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

#ifndef __JOBDIGITALTHREAD_KNOWLEDGEBASE_H_
#define __JOBDIGITALTHREAD_KNOWLEDGEBASE_H_

#include <omnetpp.h>
#include <cmath>
#include "../common/Util.h"

using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class KnowledgeBase: public cSimpleModule {
private:
    int var_num;
    int dt_num;
    double assoc_fraction;
    double assoc_chance;
    int assoc_max_num;
    // dt_num
    set<int> taskSystems;
    // dt_num
    set<int> context;
    // <dt_num + variable_key, pull chance>
    map<string, double> associations;
    void buildKnowledgeBase();
    void updateDisplayString();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
public:
    // 0 - no need to pull; 1 - must pull; (0, 1) - probabilistic
    double queryPullRate(int dt, int key);
};

#endif
