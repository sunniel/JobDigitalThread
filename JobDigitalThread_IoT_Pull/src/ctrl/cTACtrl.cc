//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "cTACtrl.h"

Define_Module(cTACtrl);

cTACtrl::cTACtrl() {
    STAGE_NUM = 2;
}

cTACtrl::~cTACtrl() {
    ;
}

int cTACtrl::numInitStages() const {
    return STAGE_NUM;
}

void cTACtrl::initialize(int stage) {
    if (stage == 0) {
        HostBase::initialize();
        fullName = getParentModule()->getFullName();
    }

    if (stage == 1) {
        TransportAddress *addr =
                UnderlayConfiguratorAccess().get()->registerEndpoint(
                        getParentModule());
        ipAddress = addr->getIp();
        IPv4InterfaceData *ipData = new IPv4InterfaceData();
        ipData->setIPAddress(ipAddress.get4());
        InterfaceEntry *ie = new InterfaceEntry();
        ie->setName("IPAddress");
        ie->setIPv4Data(ipData);
        InterfaceTable *ift = InterfaceTableAccess().get(getParentModule());
        ift->addInterface(ie);
    }
}

void cTACtrl::dispatchHandler(cMessage *msg) {
    if (msg->isName(msg::REMOTE_UPDATE)) {
        RemoteUpdate *update = check_and_cast<RemoteUpdate*>(msg);
        handleRemoteUpdate(update);
        delete msg;
    }
}

void cTACtrl::handleRemoteUpdate(RemoteUpdate *update) {
    json updates = json::parse(update->getUpdates());
    int count = update->getCount();
    json r_digest = json::parse(update->getDigest());
    int granularity = update->getGranularity();
    int round = update->getRound();
    bool isPull = update->getIsPull();

    EV << "remote updates: " << updates << endl;
    EV << "remote count: " << count << endl;
    EV << "remote granularity: " << granularity << endl;
    EV << "remote digest: " << r_digest << endl;

    // find missing update types
    json lost;

    for (auto &it : updates.items()) {
        string first = it.key();
        int msg_index = util::strToInt(first);
        receivedIndices.insert(msg_index);
        json j_update = it.value();
        int dt_index = j_update["dt_index"].get<int>();
        int u_index = j_update["u_index"].get<int>();
        cache[dt_index][u_index] = j_update;
    }

    // search missing messages
    for (int i = 0; i < count; i++) {
        if (receivedIndices.count(i) == 0) {
            lost["indices"].push_back(i);
        }
    }

    // generate local digest
    map<int, map<int, int>> l_digestMap;
    json l_digest;
    for (auto &it : cache) {
        map<int, json> dtUpdate = it.second;
        json digestDT;
        for (auto &it2 : dtUpdate) {
            json updateDetail = it2.second;
            string key = util::intToStr(updateDetail["key"]);
            if (digestDT.count(key) == 0) {
                digestDT[key] = 0;
            }
            int occurrence = digestDT[key];
            occurrence++;
            digestDT[key] = occurrence;
            l_digestMap[it.first][updateDetail["key"]] = occurrence;
        }
        l_digest[util::intToStr(it.first)] = digestDT;
    }

    // convert r_digest to map
    map<int, map<int, int>> r_digestMap;
    for (auto &it : r_digest.items()) {
        string first = it.key();
        int dt_index = util::strToInt(first);
        json digestDT = it.value();
        for (auto &it2 : digestDT.items()) {
            string key = it2.key();
            int var = util::strToInt(key);
            int count = it2.value();
            r_digestMap[dt_index][var] = count;
        }
    }

    // compare the generated and received digest
    json lost_digest;
    for (auto &it : r_digestMap) {
        int dt_index = it.first;
        json lost_dtDigest;
        bool toPull = false;
        for (auto &it2 : it.second) {
            int var = it2.first;
            // query knowledge base
            double p_pull =
                    KnowledgeBaseAccess().get(getParentModule())->queryPullRate(
                            dt_index, var);
            if (uniform(0, 1) < p_pull) {
                int count = it2.second;
                if (l_digestMap.count(dt_index) > 0
                        && l_digestMap[dt_index].count(var) > 0) {
                    int gap = count - l_digestMap[dt_index][var];
                    if (gap > 0) {
                        lost_dtDigest[util::intToStr(var)] = gap;
                        toPull = true;
                    }
                } else {
                    lost_dtDigest[util::intToStr(var)] = count;
                    toPull = true;
                }
            }
        }
        if (toPull) {
            lost_digest[util::intToStr(dt_index)] = lost_dtDigest;
        }
    }
    lost["lost_digest"] = lost_digest;

    // transmit round update to DTs
    // <dt, updates>
    map<int, json> dtLastUpdate;
    int index = 0;
    for (auto &it : cache) {
        int dtIndex = it.first;
        for (auto &it2 : it.second) {
            json dtUpdate = it2.second;
            dtUpdate["msg_index"] = index;
            string key = util::intToStr(dtUpdate["key"].get<int>());
            dtLastUpdate[dtIndex][util::intToStr(index)] = dtUpdate;
            index++;
        }
    }

    for (auto &it : dtLastUpdate) {
        string dt = "cDT[" + util::intToStr(it.first) + "]";
        json update = it.second;
        cDTUpdate *dtUpdate = new cDTUpdate(msg::cDT_UPDATE);
        dtUpdate->setUpdates(update.dump().c_str());
        dtUpdate->setRound(round);
        dtUpdate->setTs(simTime());
        IPvXAddress dest = loadAddress(dt.c_str());
        dtUpdate->setControlInfo(this->generateControlInfo(ipAddress, dest));
        sendIdeal(dtUpdate);
    }

    cache.clear();
    receivedIndices.clear();

    // for coverage analysis
    for (auto &it : l_digest.items()) {
        string dt = it.key();
        json dtDigest = it.value();
        for (auto &it2 : dtDigest.items()) {
            string key = it2.key();
            int frequency = it2.value();
            string dtKey = dt + "-" + key;
            GlobalStatisticsAccess().get()->addCloudDigest(dtKey, frequency);
        }
    }
    GlobalStatisticsAccess().get()->analyzeRoundCoverage(round);

}

void cTACtrl::finish() {

}
