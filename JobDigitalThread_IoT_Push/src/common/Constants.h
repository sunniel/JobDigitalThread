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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Display channel strings
extern const char *DISPLAY_STR_CH_TEMP;
extern const char *DISPLAY_STR_CH_HIDDEN;
extern const char *DISPLAY_STR_CH_LINK;

// Display message strings
extern const char *DISPLAY_STR_MSG_GROUP;
extern const char *DISPLAY_STR_MSG_GROUP_CC;
extern const char *DISPLAY_STR_MSG_GROUP_GR;
extern const char *DISPLAY_STR_MSG_GROUP_EH;
extern const char *DISPLAY_STR_MSG_HIDDEN;

// Display module strings
extern const char *DISPLAY_STR_MOD_HIDDEN;

// Channel type strings
extern const char *CH_TYPE_FAIR_LOSS;

// message names
namespace msg {
// timeout event
extern const char *SYSTEM_INIT;
extern const char *IIOT_TIMEOUT;
extern const char *eTA_TIMEOUT;
extern const char *cDA_TIMEOUT;

// communication
extern const char *IIOT_READ;
extern const char *eDT_UPDATE;
extern const char *cDT_UPDATE;
extern const char *cDT_LAST_UPDATE;
extern const char *REMOTE_UPDATE;
extern const char *LAST_UPDATE;
extern const char *COMMIT_UDPATE;
extern const char *DT_COMMIT;
extern const char *PULL_REQUEST;
extern const char *LAST_PULL_REQUEST;
extern const char *SIM_PULL;
}

namespace stage {
extern const int CLIENT_INIT;
extern const int NODE_CTRL_INIT;
extern const int NODE_APP_INIT;
extern const int RENDEZVOUS_INIT;
}

#endif /* CONSTANTS_H_ */
