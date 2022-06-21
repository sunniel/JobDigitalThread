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

#ifndef __MULTINODEFASTSMRSIMULATOIN_GLOBALSTATISTICS_H_
#define __MULTINODEFASTSMRSIMULATOIN_GLOBALSTATISTICS_H_

#include <omnetpp.h>
#include <cmath>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "../ctrl/KnowledgeBaseAccess.h"
#include "GlobalParametersAccess.h"
#include "../common/Constants.h"

using namespace std;
using namespace omnetpp;
using namespace boost;
using namespace boost::tuples;

class GlobalStatistics: public cSimpleModule {
private:
    unsigned long num_message;
//    int roundIndex;
//    cMessage* to;
//    simtime_t timeout;
//    simtime_t round;
    map<string, double> roundEdgeValues;
    map<string, double> roundCloudValues;
    map<string, unsigned int> roundEdgeDigest;
    map<string, unsigned int> roundCloudDigest;
    map<string, unsigned int> fullEdgeDigest;
    map<string, unsigned int> fullCloudDigest;
    // <round number, accuracy>
    map<int, double> roundAccuracy;
    // <round number, coverage>
    map<int, double> roundCoverage;

    double analyzeTraceCoverage();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
public:
    GlobalStatistics();
    void addMessage(int i);
    void addEdgeValue(string key, double value);
    void addCloudValue(string key, double value);
    void addEdgeDigest(string key, int frequency);
    void addCloudDigest(string key, int frequency);
    void analyzeRoundAccuracy(int round);
    void analyzeRoundCoverage(int round);
};

#endif
