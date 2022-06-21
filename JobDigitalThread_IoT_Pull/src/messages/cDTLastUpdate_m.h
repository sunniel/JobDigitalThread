//
// Generated file, do not edit! Created by nedtool 5.6 from messages/cDTLastUpdate.msg.
//

#ifndef __CDTLASTUPDATE_M_H
#define __CDTLASTUPDATE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "../common/Constants.h"
// }}

/**
 * Class generated from <tt>messages/cDTLastUpdate.msg:24</tt> by nedtool.
 * <pre>
 * packet cDTLastUpdate
 * {
 *     string displayString = DISPLAY_STR_MSG_GROUP;
 * 
 *     string updates;
 *     int round;
 *     simtime_t ts;
 * }
 * </pre>
 */
class cDTLastUpdate : public ::omnetpp::cPacket
{
  protected:
    ::omnetpp::opp_string displayString;
    ::omnetpp::opp_string updates;
    int round;
    ::omnetpp::simtime_t ts;

  private:
    void copy(const cDTLastUpdate& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const cDTLastUpdate&);

  public:
    cDTLastUpdate(const char *name=nullptr, short kind=0);
    cDTLastUpdate(const cDTLastUpdate& other);
    virtual ~cDTLastUpdate();
    cDTLastUpdate& operator=(const cDTLastUpdate& other);
    virtual cDTLastUpdate *dup() const override {return new cDTLastUpdate(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getDisplayString() const;
    virtual void setDisplayString(const char * displayString);
    virtual const char * getUpdates() const;
    virtual void setUpdates(const char * updates);
    virtual int getRound() const;
    virtual void setRound(int round);
    virtual ::omnetpp::simtime_t getTs() const;
    virtual void setTs(::omnetpp::simtime_t ts);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const cDTLastUpdate& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, cDTLastUpdate& obj) {obj.parsimUnpack(b);}


#endif // ifndef __CDTLASTUPDATE_M_H

