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

#ifndef __JOBDIGITALTHREAD_CTACTRL_H_
#define __JOBDIGITALTHREAD_CTACTRL_H_

#include <omnetpp.h>
#include <nlohmann/json.hpp>
#include "../common/HostBase.h"
#include "../global/UnderlayConfiguratorAccess.h"
#include "../global/GlobalStatisticsAccess.h"
#include "../messages/RemoteUpdate_m.h"
#include "../messages/LastUpdate_m.h"
#include "../messages/cDTUpdate_m.h"
#include "../messages/cDTLastUpdate_m.h"
#include "../messages/PullRequest_m.h"
#include "KnowledgeBaseAccess.h"

using namespace std;
using namespace omnetpp;
using json = nlohmann::json;

/**
 * TODO - Generated class
 */
class cTACtrl : public HostBase
{
private:
    int STAGE_NUM;
    // cache updates from DTs, in <DT, <index, update>>
    map<int, map<int, json>> cache;
    map<int, map<int, json>> last_cache;
    set<int> receivedIndices;
    set<int> last_receivedIndices;
    double pull_threshold;
    double assoc_accuracy;
    void handleRemoteUpdate(RemoteUpdate *update);
    void handleLastUpdate(LastUpdate *update);
protected:
    virtual int numInitStages() const;
    virtual void initialize(int stage);
    virtual void dispatchHandler(cMessage *msg);
    virtual void finish();
public:
    cTACtrl();
    virtual ~cTACtrl();
};

#endif
