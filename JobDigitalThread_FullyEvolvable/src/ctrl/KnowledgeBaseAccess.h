/**
 * @file KnowledgeBaseAccess.h
 * @author
 */

#ifndef __KNOWLEDGEBASE_ACCESS_H__
#define __KNOWLEDGEBASE_ACCESS_H__

#include <omnetpp.h>
#include "KnowledgeBase.h"

/**
 * Gives access to the KnowledgeBase module.
 */
class KnowledgeBaseAccess {
public:

    /**
     * returns the KnowledgeBase module
     *
     * @return the KnowledgeBase module
     */
    KnowledgeBase* get(cModule* parent) {
        return (KnowledgeBase*) parent->getSubmodule("knowledgeBase");
    }
};

#endif
