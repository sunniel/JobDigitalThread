#ifndef __INTERFACETABLEACCESS_H_
#define __INTERFACETABLEACCESS_H_

#include <omnetpp.h>
#include "InterfaceTable.h"

/**
 * Gives access to the InterfaceTable module in the given parent module.
 *
 */
class InterfaceTableAccess {
public:
    /**
     * returns the InterfaceTable module in the given parent module
     *
     * @return the InterfaceTable module
     */
    InterfaceTable* get(cModule* parent) {
        return (InterfaceTable*) parent->getSubmodule("interfaceTable");
    }
};

#endif /* INTERFACETABLEACCESS_H_ */
