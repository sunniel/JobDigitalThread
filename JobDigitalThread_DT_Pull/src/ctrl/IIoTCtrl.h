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

#ifndef __JOBDIGITALTHREAD_IIOTCTRL_H_
#define __JOBDIGITALTHREAD_IIOTCTRL_H_

#include <omnetpp.h>
#include "../common/HostBase.h"
#include "../global/UnderlayConfiguratorAccess.h"
#include "../messages/Read_m.h"

using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class IIoTCtrl: public HostBase
{
private:
    int STAGE_NUM;
    int key;
    double value;
    cMessage* to;
    simtime_t timeout;
    simtime_t cycle;
    int cycleIndex;
protected:
    virtual int numInitStages() const;
    virtual void initialize(int stage);
    virtual void dispatchHandler(cMessage *msg);
    virtual void finish();
public:
    IIoTCtrl();
    virtual ~IIoTCtrl();
};

#endif
