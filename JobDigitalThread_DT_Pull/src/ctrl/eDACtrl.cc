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

#include "eDACtrl.h"

Define_Module(eDACtrl);

eDACtrl::eDACtrl() {
    STAGE_NUM = 2;
}

eDACtrl::~eDACtrl() {
    ;
}

int eDACtrl::numInitStages() const {
    return STAGE_NUM;
}

void eDACtrl::initialize(int stage) {
    if (stage == 0) {
        HostBase::initialize();
        fullName = getParentModule()->getFullName();
        index = getParentModule()->getIndex();
        var_num = par("var_num");
        for (int i = 0; i < var_num; i++) {
            state[i] = 0;
        }
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

void eDACtrl::dispatchHandler(cMessage *msg) {
    if (msg->isName(msg::IIOT_READ)) {
        Read *read = check_and_cast<Read*>(msg);
        handleSenUpdate(read);
        delete msg;
    }
}

void eDACtrl::handleSenUpdate(Read *read) {
    int var = read->getVariable();
    state[var] = read->getValue();

    // send update to cTA
    eDTUpdate *update = new eDTUpdate(msg::eDT_UPDATE);
    update->setDt(fullName);
    update->setIndex(index);
    update->setVariable(read->getVariable());
    update->setValue(read->getValue());
    update->setTs(read->getTs());
    // get eTA address
    IPvXAddress eTAAddress = loadAddress("eTAAddress");
    update->setControlInfo(generateControlInfo(ipAddress, eTAAddress));
    r_transmit(update, eTAAddress);

}

void eDACtrl::finish() {

}
