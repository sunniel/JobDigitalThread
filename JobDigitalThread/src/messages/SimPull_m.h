//
// Generated file, do not edit! Created by nedtool 5.6 from messages/SimPull.msg.
//

#ifndef __SIMPULL_M_H
#define __SIMPULL_M_H

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
 * Class generated from <tt>messages/SimPull.msg:24</tt> by nedtool.
 * <pre>
 * packet SimPull
 * {
 *     string displayString = DISPLAY_STR_MSG_GROUP;
 * 
 *     int dt;
 *     int round;
 *     simtime_t ts;
 * }
 * </pre>
 */
class SimPull : public ::omnetpp::cPacket
{
  protected:
    ::omnetpp::opp_string displayString;
    int dt;
    int round;
    ::omnetpp::simtime_t ts;

  private:
    void copy(const SimPull& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SimPull&);

  public:
    SimPull(const char *name=nullptr, short kind=0);
    SimPull(const SimPull& other);
    virtual ~SimPull();
    SimPull& operator=(const SimPull& other);
    virtual SimPull *dup() const override {return new SimPull(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getDisplayString() const;
    virtual void setDisplayString(const char * displayString);
    virtual int getDt() const;
    virtual void setDt(int dt);
    virtual int getRound() const;
    virtual void setRound(int round);
    virtual ::omnetpp::simtime_t getTs() const;
    virtual void setTs(::omnetpp::simtime_t ts);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SimPull& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SimPull& obj) {obj.parsimUnpack(b);}


#endif // ifndef __SIMPULL_M_H

