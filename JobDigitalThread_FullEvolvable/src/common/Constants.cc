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

#include "Constants.h"

const char* DISPLAY_STR_CH_TEMP = "m=auto;ls=red,3,dashed";
const char* DISPLAY_STR_CH_HIDDEN = "ls=,0";
const char* DISPLAY_STR_CH_LINK = "m=auto;ls=black,1,solid";

const char* DISPLAY_STR_MSG_GROUP = "b=10,10,oval,black,kind,0";
const char* DISPLAY_STR_MSG_GROUP_CC = "b=10,10,oval,blue,kind,0";
const char* DISPLAY_STR_MSG_GROUP_GR = "b=10,10,oval,yellow,kind,0";
const char* DISPLAY_STR_MSG_GROUP_EH = "b=10,10,oval,cyan,kind,0";
const char* DISPLAY_STR_MSG_HIDDEN = "b=-1,-1,,green,kind,3";

const char* DISPLAY_STR_MOD_HIDDEN = "i=block/downarrow";

const char* CH_TYPE_FAIR_LOSS = "common.FairLossChannel";

// timeout event
const char* msg::SYSTEM_INIT = "SYSTEM_INIT";
const char* msg::IIOT_TIMEOUT = "IIOT_TIMEOUT";
const char* msg::eTA_TIMEOUT = "eTA_TIMEOUT";
const char* msg::cDA_TIMEOUT = "cDA_TIMEOUT";

// communication
const char* msg::IIOT_READ = "IIOT_UPDATE";
const char* msg::eDT_UPDATE = "eDT_UPDATE";
const char* msg::cDT_UPDATE = "cDT_UPDATE";
const char* msg::cDT_LAST_UPDATE = "cDT_LAST_UPDATE";
const char* msg::REMOTE_UPDATE = "REMOTE_UPDATE";
const char* msg::LAST_UPDATE = "LAST_UPDATE";
const char* msg::COMMIT_UDPATE = "COMMIT_UDPATE";
const char* msg::DT_COMMIT = "DT_COMMIT";
const char* msg::PULL_REQUEST = "PULL_REQUEST";
const char* msg::LAST_PULL_REQUEST = "LAST_PULL_REQUEST";
const char* msg::SIM_PULL = "SIM_PULL";

// number of initialization stage
const int stage::CLIENT_INIT = 2;
const int stage::NODE_CTRL_INIT = 2;
const int stage::NODE_APP_INIT = 2;
const int stage::RENDEZVOUS_INIT = 2;
