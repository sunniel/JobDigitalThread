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

#include "UnderlayConfigurator.h"

Define_Module(UnderlayConfigurator);

UnderlayConfigurator::UnderlayConfigurator() {
    edgeSystemCreated = 0;
    cloudSystemCreated = 0;
}

UnderlayConfigurator::~UnderlayConfigurator() {
//    disposeFailures();
}

int UnderlayConfigurator::numInitStages() const {
    return 1;
}

void UnderlayConfigurator::initialize(int stage) {
    nextFreeAddress = 0x1000001;
    globalNodeList = GlobalNodeListAccess().get();
    parameterList = GlobalParametersAccess().get();

    WATCH_MAP(death_schedule);

    // initialize clients
    cMessage* systemInit = new cMessage(msg::SYSTEM_INIT);
    scheduleAt(0, systemInit);
}

void UnderlayConfigurator::handleMessage(cMessage *msg) {
    if (msg->isName(msg::SYSTEM_INIT)) {
        handleSystemInit(msg);
    }
}

TransportAddress* UnderlayConfigurator::registerEndpoint(cModule *host) {
    IPvXAddress addr = IPAddress(nextFreeAddress++);
    // create meta information
    SimpleNodeEntry *entry = new SimpleNodeEntry(host);
    SimpleInfo *info = new SimpleInfo(host->getId(), host->getFullName());
    info->setEntry(entry);
    //add node to bootstrap oracle
    globalNodeList->addPeer(addr, info);

    TransportAddress *address = new TransportAddress(addr);
    return address;
}

void UnderlayConfigurator::handleSystemInit(cMessage *msg) {
    // initialize clients
    int systemNum = getSimulation()->getSystemModule()->par("system_num");
    const char *edgeSystemType = par("edgeSystemType");
    const char *edgeSystemName = par("edgeSystemName");
    const char *cloudSystemType = par("cloudSystemType");
    const char *cloudSystemName = par("cloudSystemName");
    cModule* eTA = getParentModule()->getSubmodule("remoteSite")->getSubmodule("eTA");
    IPvXAddress eTAAddress = getIPAddress(eTA);
    cModule* cTA = getParentModule()->getSubmodule("supervisorySite")->getSubmodule("cTA");
    IPvXAddress cTAAddress = getIPAddress(cTA);
    for (int i = 0; i < systemNum; i++) {
        // create a new edge system
        cModuleType *moduleType = cModuleType::get(edgeSystemType);
        cModule *parent = getParentModule()->getSubmodule("remoteSite");
        // create (possibly compound) module and build its submodules (if any)
        cModule *edgeSystem = moduleType->create(edgeSystemName, parent,
                edgeSystemCreated + 1, edgeSystemCreated);
        edgeSystemCreated++;
        // set up parameters, if any
        edgeSystem->finalizeParameters();
        edgeSystem->buildInside();
        // create activation message
        edgeSystem->scheduleStart(simTime());
        edgeSystem->callInitialize(0);
        edgeSystem->callInitialize(1);
        // assign eTA address to eDA
        IPv4InterfaceData* ipData = new IPv4InterfaceData();
        ipData->setIPAddress(eTAAddress.get4());
        InterfaceEntry* ie = new InterfaceEntry();
        ie->setName("eTAAddress");
        ie->setIPv4Data(ipData);
        InterfaceTable* ift = InterfaceTableAccess().get(edgeSystem);
        ift->addInterface(ie);

        // create a new cloud system
        moduleType = cModuleType::get(cloudSystemType);
        parent = getParentModule()->getSubmodule("supervisorySite");
        // create (possibly compound) module and build its submodules (if any)
        cModule *cloudSystem = moduleType->create(cloudSystemName, parent,
                cloudSystemCreated + 1, cloudSystemCreated);
        cloudSystemCreated++;
        // set up parameters, if any
        cloudSystem->finalizeParameters();
        cloudSystem->buildInside();
        // create activation message
        cloudSystem->scheduleStart(simTime());
        cloudSystem->callInitialize(0);
        cloudSystem->callInitialize(1);
        // assign cTA address to cDA
        ipData = new IPv4InterfaceData();
        ipData->setIPAddress(cTAAddress.get4());
        ie = new InterfaceEntry();
        ie->setName("cTAAddress");
        ie->setIPv4Data(ipData);
        ift = InterfaceTableAccess().get(cloudSystem);
        ift->addInterface(ie);
        // assign cDA address to cTA
        IPvXAddress cDAAddress = getIPAddress(cloudSystem);
        ipData = new IPv4InterfaceData();
        ipData->setIPAddress(cDAAddress.get4());
        ie = new InterfaceEntry();
        ie->setName(cloudSystem->getFullName());
        ie->setIPv4Data(ipData);
        ift = InterfaceTableAccess().get(cTA);
        ift->addInterface(ie);
        // assign eTA address to cDA
        ipData = new IPv4InterfaceData();
        ipData->setIPAddress(eTAAddress.get4());
        ie = new InterfaceEntry();
        ie->setName("eTAAddress");
        ie->setIPv4Data(ipData);
        ift = InterfaceTableAccess().get(cloudSystem);
        ift->addInterface(ie);
    }

    // eTA and cTA learn the address of each other
    IPv4InterfaceData *ipData = new IPv4InterfaceData();
    ipData->setIPAddress(cTAAddress.get4());
    InterfaceEntry *ie = new InterfaceEntry();
    ie->setName("cTAAddress");
    ie->setIPv4Data(ipData);
    InterfaceTable *ift = InterfaceTableAccess().get(eTA);
    ift->addInterface(ie);

    ipData = new IPv4InterfaceData();
    ipData->setIPAddress(eTAAddress.get4());
    ie = new InterfaceEntry();
    ie->setName("eTAAddress");
    ie->setIPv4Data(ipData);
    ift = InterfaceTableAccess().get(cTA);
    ift->addInterface(ie);

    delete msg;
}

IPvXAddress UnderlayConfigurator::getIPAddress(cModule* module){
    InterfaceTable* ift = InterfaceTableAccess().get(module);
    InterfaceEntry* ie = ift->getInterfaceByName("IPAddress");
    IPv4InterfaceData* ipData = ie->ipv4Data();
    IPvXAddress addr(ipData->getIPAddress());
    return addr;
}
