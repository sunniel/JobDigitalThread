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

#include "eTACtrl.h"

Define_Module(eTACtrl);

eTACtrl::eTACtrl() {
    STAGE_NUM = 2;
    timeout = 0;
    roundIndex = 0;
}

eTACtrl::~eTACtrl() {
    ;
}

int eTACtrl::numInitStages() const {
    return STAGE_NUM;
}

void eTACtrl::initialize(int stage) {
    if (stage == 0) {
        HostBase::initialize();
        fullName = getParentModule()->getFullName();
        msgLossRate = getParentModule()->par("message_loss");
        round = GlobalParametersAccess().get()->getRound();
        timeout += round;
        to = new cMessage(msg::eTA_TIMEOUT);
        scheduleAt(timeout, to);

        WATCH_MAP(cache);
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

void eTACtrl::dispatchHandler(cMessage *msg) {
    if (msg->isName(msg::eTA_TIMEOUT)) {
        handleRoundSyn();
        timeout += round;
        scheduleAt(timeout, msg);
    } else if (msg->isName(msg::eDT_UPDATE)) {
        eDTUpdate *update = check_and_cast<eDTUpdate*>(msg);
        handleDTUpdate(update);
        delete msg;
    } else if (msg->isName(msg::COMMIT_UDPATE)) {
        handleCommit();
        delete msg;
    }  else if (msg->isName(msg::DT_COMMIT)) {
        DTCommit *commit = check_and_cast<DTCommit*>(msg);
        handleDTCommit(commit);
        delete msg;
    }
}

void eTACtrl::handleRoundSyn() {

    if (roundIndex > 0) {
        GlobalStatisticsAccess().get()->analyzeRoundAccuracy(roundIndex);
    }

    roundIndex++;

    // clear caches
    if (!updates.is_null())
        updates.clear();
    if (!digest.is_null())
        digest.clear();

    // generate complete updates
    int index = 0;
    json success;
    for (auto &it : cache) {
        int dtIndex = it.first;
        map<int, json> dtUpdate = it.second;
        json digestDT;
        for (auto &it2 : dtUpdate) {
            int dtUpdateIndex = it2.first;
            json &updateDetail = it2.second;
            cache[dtIndex][dtUpdateIndex]["msg_index"] = index;
            if (cache[dtIndex][dtUpdateIndex]["round"].is_null()) {
                cache[dtIndex][dtUpdateIndex]["round"] = roundIndex;
            }
            updates[util::intToStr(index)] = updateDetail;
            if (uniform(0, 1) < (1 - msgLossRate)) {
                success[util::intToStr(index)] = updateDetail;
            }
            index++;

            string key = util::intToStr(updateDetail["key"]);
            if (digestDT.count(key) == 0) {
                digestDT[key] = 0;
            }
            int occurrence = digestDT[key];
            occurrence++;
            digestDT[key] = occurrence;
        }
        digest[util::intToStr(dtIndex)] = digestDT;
    }
    if (index > 0) {
        RemoteUpdate *update = new RemoteUpdate(msg::REMOTE_UPDATE);
        update->setUpdates(success.dump().c_str());
        update->setCount(index);
        update->setGranularity(GranularityType::VARIABLE);
        update->setDigest(digest.dump().c_str());
        update->setRound(roundIndex);
        update->setIsPull(false);
        update->setTs(simTime());
        IPvXAddress cTAAddress = loadAddress("cTAAddress");
        update->setControlInfo(generateControlInfo(ipAddress, cTAAddress));
        sendIdeal(update);

        // updates + count + granularity + digest
        GlobalStatisticsAccess().get()->addMessage(updates.size() + 1 + 1 + 1);
    }

    EV << "push: " << updates << endl;

    // for accuracy analysis
    for (auto &it : cache) {
        int dtIndex = it.first;
        map<int, json> dtUpdates = it.second;
        // <var, last update>
        map<int, json> lastUpdates;
        json last_digestDT;
        for (auto &it2 : dtUpdates) {
            json updateDetail = it2.second;
            int key = updateDetail["key"];
            if (lastUpdates.count(key) == 0
                    || lastUpdates[key]["time"] < updateDetail["time"]) {
                lastUpdates[key] = updateDetail;
            }
        }
        for (auto &it2 : lastUpdates) {
            string key = util::intToStr(dtIndex) + "-"
                    + util::intToStr(it2.first);
            GlobalStatisticsAccess().get()->addEdgeValue(key,
                    it2.second["value"].get<int>());
        }
    }
    // for coverage analysis
    for (auto &it : digest.items()) {
        string dt = it.key();
        json dtDigest = it.value();
        for (auto &it2 : dtDigest.items()) {
            string key = it2.key();
            int frequency = it2.value();
            string dtKey = dt + "-" + key;
            GlobalStatisticsAccess().get()->addEdgeDigest(dtKey, frequency);
        }
    }
}

void eTACtrl::handleDTUpdate(eDTUpdate *update) {
    json dtUpdate;
    dtUpdate["dt"] = update->getDt();
    dtUpdate["dt_index"] = update->getIndex();
    dtUpdate["key"] = update->getVariable();
    dtUpdate["value"] = update->getValue();
    dtUpdate["time"] = update->getTs().dbl();
    int dt = update->getIndex();
    if (updateIndex.count(dt) == 0) {
        updateIndex[dt] = 0;
    }
    if (cache[dt] == 0) {
        map<int, json> updateMap;
        cache[dt] = updateMap;
    }
    dtUpdate["u_index"] = updateIndex[dt];
    cache[dt][updateIndex[dt]] = dtUpdate;
    updateIndex[dt]++;
}

void eTACtrl::handleDTCommit(DTCommit *commit) {
    int dtIndex = commit->getDt();
    updateIndex.erase(dtIndex);
    cache.erase(dtIndex);
    string strIndex = util::intToStr(dtIndex);
    if (!digest.is_null()) {
        digest.erase(strIndex);
    }
}

void eTACtrl::handleCommit() {
    updateIndex.clear();
    cache.clear();
    if (!updates.is_null()) {
        updates.clear();
    }
    if (!digest.is_null()) {
        digest.clear();
    }
}

void eTACtrl::finish() {
    if (to != NULL) {
        cancelAndDelete(to);
    }
}
