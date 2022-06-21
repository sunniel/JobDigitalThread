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

#include "GlobalStatistics.h"

Define_Module(GlobalStatistics);

GlobalStatistics::GlobalStatistics() {
    num_message = 0;
}

void GlobalStatistics::initialize() {
    WATCH_MAP(roundEdgeValues);
    WATCH_MAP(roundCloudValues);
    WATCH_MAP(roundEdgeDigest);
    WATCH_MAP(roundCloudDigest);
}

void GlobalStatistics::handleMessage(cMessage *msg) {
    ;
}

void GlobalStatistics::addMessage(int i) {
    num_message += (long) i;
}

void GlobalStatistics::addEdgeValue(string key, double value) {
    roundEdgeValues[key] = value;
}
void GlobalStatistics::addCloudValue(string key, double value) {
    roundCloudValues[key] = value;
}

void GlobalStatistics::addEdgeDigest(string key, int frequency) {
    if (roundEdgeDigest.count(key) == 0) {
        roundEdgeDigest[key] = 0;
    }
    roundEdgeDigest[key] += frequency;
    if (fullEdgeDigest.count(key) == 0) {
        fullEdgeDigest[key] = 0;
    }
    fullEdgeDigest[key] += frequency;
}
void GlobalStatistics::addCloudDigest(string key, int frequency) {
    if (roundCloudDigest.count(key) == 0) {
        roundCloudDigest[key] = 0;
    }
    roundCloudDigest[key] += frequency;
    if (fullCloudDigest.count(key) == 0) {
        fullCloudDigest[key] = 0;
    }
    fullCloudDigest[key] += frequency;
}

void GlobalStatistics::analyzeRoundAccuracy(int round) {
    double totalError = 0;
    double totalValue = 0;
    for (auto it : roundEdgeValues) {
        double actualValue = it.second;
        double syncedValue = 0;
        if (roundCloudValues.count(it.first) > 0) {
            syncedValue = roundCloudValues[it.first];
        }
        double error = fabs(actualValue - syncedValue);
        totalError += error;
        totalValue += actualValue;
    }

    double accuracy = 1 - totalError / totalValue;
    roundAccuracy[round] = accuracy;
    roundEdgeValues.clear();
    roundCloudValues.clear();
}

void GlobalStatistics::analyzeRoundCoverage(int round) {
    int edgeUpdateFrequency = 0;
    int cloudUpdateFrequency = 0;
    cModule *kbParent = getModuleByPath("CJDTG.supervisorySite.cTA");
    for (auto it : roundEdgeDigest) {
        string dtKey = it.first;
        vector<string> container;
        util::splitString(dtKey, "-", container);
        int dtIndex = util::strToInt(container[0]);
        int key = util::strToInt(container[1]);
        double p_pull = KnowledgeBaseAccess().get(kbParent)->queryPullRate(
                dtIndex, key);
        if (p_pull > 0) {
            edgeUpdateFrequency += it.second;
        }
    }
    for (auto it : roundCloudDigest) {
        string dtKey = it.first;
        vector<string> container;
        util::splitString(dtKey, "-", container);
        int dtIndex = util::strToInt(container[0]);
        int key = util::strToInt(container[1]);
        double p_pull = KnowledgeBaseAccess().get(kbParent)->queryPullRate(
                dtIndex, key);
        if (p_pull > 0) {
            cloudUpdateFrequency += it.second;
        }
    }

    double coverage = 1;
    if (cloudUpdateFrequency != 0) {
        coverage = (double) cloudUpdateFrequency / edgeUpdateFrequency;
    }
    roundCoverage[round] = coverage;
    roundEdgeDigest.clear();
    roundCloudDigest.clear();
}

double GlobalStatistics::analyzeTraceCoverage() {
    int edgeUpdateFrequency = 0;
    int cloudUpdateFrequency = 0;
    cModule *kbParent = getModuleByPath("CJDTG.supervisorySite.cTA");
    for (auto it : fullEdgeDigest) {
        string dtKey = it.first;
        vector<string> container;
        util::splitString(dtKey, "-", container);
        int dtIndex = util::strToInt(container[0]);
        int key = util::strToInt(container[1]);
        double p_pull = KnowledgeBaseAccess().get(kbParent)->queryPullRate(
                dtIndex, key);
        if (p_pull > 0) {
            edgeUpdateFrequency += it.second;
        }
    }
    for (auto it : fullCloudDigest) {
        string dtKey = it.first;
        vector<string> container;
        util::splitString(dtKey, "-", container);
        int dtIndex = util::strToInt(container[0]);
        int key = util::strToInt(container[1]);
        double p_pull = KnowledgeBaseAccess().get(kbParent)->queryPullRate(
                dtIndex, key);
        if (p_pull > 0) {
            cloudUpdateFrequency += it.second;
        }
    }

    double coverage = 1;
    if (cloudUpdateFrequency != 0) {
        coverage = (double) cloudUpdateFrequency / edgeUpdateFrequency;
    }
    return coverage;
}

void GlobalStatistics::finish() {
    cout << "Generating statistical results" << endl;

    cout << endl;
    cout << "Generating round accuracy" << endl;
    for (auto it : roundAccuracy) {
        cout << "Round " << it.first << " trace accuracy: " << it.second
                << endl;
    }
    cout << endl;

    cout << endl;
    cout << "Generating round coverage" << endl;
    for (auto it : roundCoverage) {
        cout << "Round " << it.first << " trace coverage: " << it.second
                << endl;
    }
    cout << endl;

    cout << "Generated communication overhead: " << num_message << endl;

    double traceCoverage = analyzeTraceCoverage();
    recordScalar("Trace Coverage", traceCoverage);
    recordScalar("Communication Overhead", num_message);

}
