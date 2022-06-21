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

#include "KnowledgeBase.h"

Define_Module(KnowledgeBase);

void KnowledgeBase::initialize() {
    var_num = par("var_num");
    dt_num = par("system_num");
    assoc_fraction = par("assoc_fraction");
    assoc_chance = par("assoc_chance");
    assoc_max_num = par("assoc_max_num");
    buildKnowledgeBase();
    updateDisplayString();
    WATCH_SET(taskSystems);
    WATCH_SET(context);
    WATCH_MAP(associations);
}

void KnowledgeBase::updateDisplayString() {
    if (!cComponent::hasGUI())
        return;

    char buf[80];
    sprintf(buf, "System DT: %d\nContext DT: %d\nAssociation: %d",
            taskSystems.size(), context.size(), associations.size());
    getDisplayString().setTagArg("t", 0, buf);
}

/**
 * Not used
 */
void KnowledgeBase::handleMessage(cMessage *msg) {
    // TODO - Generated method body
}

void KnowledgeBase::buildKnowledgeBase() {
    for (int i = 0; i < dt_num; i++) {
        if (i % 2 == 0) {
            taskSystems.insert(i);
        } else {
            context.insert(i);
            for (int j = 0; j < var_num; j++) {
                if (uniform(0, 1) < assoc_fraction) {
                    // calculate association chance
                    int assocNum = uniform(1, assoc_max_num + 1);
                    double chance = 1 - pow((1 - assoc_chance), assocNum);
                    string id = util::intToStr(i) + "-" + util::intToStr(j);
                    associations[id] = chance;
                }
            }

        }
    }
}

double KnowledgeBase::queryPullRate(int dt, int key) {
    if (taskSystems.count(dt) > 0) {
        return 1;
    } else {
        string id = util::intToStr(dt) + "-" + util::intToStr(key);
        if (associations.count(id) == 0) {
            return 0;
        } else {
            return associations[id];
        }
    }
}
