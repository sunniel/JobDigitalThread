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

#include "cDACtrl.h"

Define_Module(cDACtrl);

cDACtrl::cDACtrl() {
    STAGE_NUM = 2;
    timeout = simTime();
    sample = 1;
}

cDACtrl::~cDACtrl() {
    ;
}

int cDACtrl::numInitStages() const {
    return STAGE_NUM;
}

void cDACtrl::initialize(int stage) {
    if (stage == 0) {
        HostBase::initialize();
        fullName = getParentModule()->getFullName();
        index = getParentModule()->getIndex();
        var_num = par("var_num");
        for (int i = 0; i < var_num; i++) {
            state[i] = 0;
        }
        pull_threshold = par("pull_threshold");
        sigma_base = par("sigma_base");
        sigma = sigma_base;
        sigma_max = par("sigma_max");
        pull_beta = par("pull_beta");
        pull_radix = par("pull_radix");
        sample_len = par("sample_len");
        cycle = GlobalParametersAccess().get()->getCycle();
        round = GlobalParametersAccess().get()->getRound();
        timeout += cycle;
        to = new cMessage(msg::cDA_TIMEOUT);

        // select evolvable systems
//        if(index % 2 == 0){
//            scheduleAt(timeout, to);
//        }

        WATCH_MAP(state);
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

void cDACtrl::dispatchHandler(cMessage *msg) {
    if (msg->isName(msg::cDT_LAST_UPDATE)) {
        cDTLastUpdate *update = check_and_cast<cDTLastUpdate*>(msg);
        handleDTLastUpdate(update);
        delete msg;
    }
//    else if (msg->isName(msg::cDA_TIMEOUT)) {
//        handleCycleUpdate();
//        timeout += cycle;
//        scheduleAt(timeout, msg);
//    }
}

void cDACtrl::handleDTLastUpdate(cDTLastUpdate *update) {
    int roundIndex = update->getRound();

    sigma = sample * pull_beta * sigma;
    sigma = sigma > sigma_max ? sigma_max : sigma;
    // simulate-pull determination by checking sample length
    double p_var = 1 - 1.5 / (pow(pull_radix, pull_beta) * log(100 * sigma));
    double p_pull = 0;
    if (p_var >= 1) {
        p_pull = 1;
    } else if (p_var < 0) {
        p_pull = 0;
    } else {
        p_pull = p_var;
    }

    for (auto &it : state) {
        it.second = it.second + (1 + sigma) * (round / cycle - 1);
    }

//    cout << "sample: " << sample << endl;
//    cout << "p_var: " << p_var << endl;
//    cout << "p_pull: " << p_pull << endl;
//    cout << "sigma: " << sigma << endl;

    if (sample < sample_len) {
        sample++;
    } else {
        sample = 1;
        sigma = sigma_base;
    }

    // DT commit
    DTCommit *commit = new DTCommit(msg::DT_COMMIT);
    commit->setDt(index);
    IPvXAddress dest = loadAddress("eTAAddress");
    commit->setControlInfo(this->generateControlInfo(ipAddress, dest));
    sendIdeal(commit);

    GlobalStatisticsAccess().get()->addMessage(1);
    for (auto it : state) {
        string key = util::intToStr(index) + "-" + util::intToStr(it.first);
        GlobalStatisticsAccess().get()->addCloudValue(key, it.second);
    }
}

/**
 * Currently not used
 */
void cDACtrl::handleCycleUpdate() {
    double sigma = uniform(0, 1);
    double beta = 1.0;
    double radix = 1.5;
    double p_pull = 1.0 - (pow(radix, beta) * log(100 * sigma));

    // simulate-pull determination
    if (uniform(0, 1) < p_pull) {
        cMessage *pull = new cMessage(msg::SIM_PULL);
        IPvXAddress dest = this->loadAddress("eTAAddress");
        pull->setControlInfo(generateControlInfo(ipAddress, dest));
        r_transmit(pull, dest);
    }
}

void cDACtrl::finish() {
    if (to != NULL) {
        cancelAndDelete(to);
    }
}
