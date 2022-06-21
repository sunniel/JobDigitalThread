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

#ifndef __JOBDIGITALTHREAD_CDACTRL_H_
#define __JOBDIGITALTHREAD_CDACTRL_H_

#include <omnetpp.h>
#include <cmath>
#include <nlohmann/json.hpp>
#include "../common/HostBase.h"
#include "../global/UnderlayConfiguratorAccess.h"
#include "../global/GlobalStatisticsAccess.h"
#include "../messages/cDTUpdate_m.h"
#include "../messages/cDTLastUpdate_m.h"
#include "../messages/SimPull_m.h"
#include "../messages/DTCommit_m.h"

using namespace std;
using namespace omnetpp;
using json = nlohmann::json;

/**
 * TODO - Generated class
 */
class cDACtrl: public HostBase {
private:
    int STAGE_NUM;
    int index;
    // <key, value> of state variables
    map<int, double> state;
    int var_num;
    double pull_threshold;
    double p_target;
    double pull_beta;
    double pull_radix;
    double sigma;
    double sigma_base;
    double sigma_max;
    int sample_len;
    int sample;
    // <key, last update time> of state variables
    map<int, simtime_t> lastUpdates;

    cMessage* to;
    simtime_t timeout;
    simtime_t cycle;
    simtime_t round;

    void handleDTUpdate(cDTUpdate *update);
    void handleDTLastUpdate(cDTLastUpdate *update);
    void handleCycleUpdate();
protected:
    virtual int numInitStages() const;
    virtual void initialize(int stage);
    virtual void dispatchHandler(cMessage *msg);
    virtual void finish();
public:
    cDACtrl();
    virtual ~cDACtrl();
};

#endif
