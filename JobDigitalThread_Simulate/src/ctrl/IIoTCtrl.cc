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

#include "IIoTCtrl.h"

Define_Module(IIoTCtrl);

IIoTCtrl::IIoTCtrl() {
    STAGE_NUM = 2;
    timeout = simTime();
    value = 0;
}

IIoTCtrl::~IIoTCtrl() {
    ;
}

int IIoTCtrl::numInitStages() const {
    return STAGE_NUM;
}

void IIoTCtrl::initialize(int stage) {
    if (stage == 0) {
        HostBase::initialize();
        fullName = this->getFullName();
        key = this->getIndex();
        cycle = GlobalParametersAccess().get()->getCycle();
        timeout += cycle;
        to = new cMessage(msg::IIOT_TIMEOUT);
        scheduleAt(timeout, to);
    }

    if (stage == 1) {
        TransportAddress *addr =
                UnderlayConfiguratorAccess().get()->registerEndpoint(
                        getParentModule());
        ipAddress = addr->getIp();
    }
}

void IIoTCtrl::dispatchHandler(cMessage *msg) {
    if (msg->isName(msg::IIOT_TIMEOUT)) {
//        if(uniform(0, 1) >= 0.5){
            value ++;
//        }

        Read *read = new Read(msg::IIOT_READ);
        read->setVariable(key);
        read->setValue(value);
        read->setTs(simTime());
        this->sendMsg(read, "senlink", cGate::OUTPUT);

        timeout += cycle;
        scheduleAt(timeout, msg);
    }
}

void IIoTCtrl::finish() {
    if (to != NULL) {
        cancelAndDelete(to);
    }
}
