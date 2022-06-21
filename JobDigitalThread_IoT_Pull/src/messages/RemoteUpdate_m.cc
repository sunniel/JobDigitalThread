//
// Generated file, do not edit! Created by nedtool 5.6 from messages/RemoteUpdate.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "RemoteUpdate_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(RemoteUpdate)

RemoteUpdate::RemoteUpdate(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->displayString = DISPLAY_STR_MSG_GROUP;
    this->granularity = 0;
    this->count = 0;
    this->round = 0;
    this->isPull = false;
    this->ts = 0;
}

RemoteUpdate::RemoteUpdate(const RemoteUpdate& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RemoteUpdate::~RemoteUpdate()
{
}

RemoteUpdate& RemoteUpdate::operator=(const RemoteUpdate& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RemoteUpdate::copy(const RemoteUpdate& other)
{
    this->displayString = other.displayString;
    this->updates = other.updates;
    this->granularity = other.granularity;
    this->count = other.count;
    this->digest = other.digest;
    this->round = other.round;
    this->isPull = other.isPull;
    this->ts = other.ts;
}

void RemoteUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->displayString);
    doParsimPacking(b,this->updates);
    doParsimPacking(b,this->granularity);
    doParsimPacking(b,this->count);
    doParsimPacking(b,this->digest);
    doParsimPacking(b,this->round);
    doParsimPacking(b,this->isPull);
    doParsimPacking(b,this->ts);
}

void RemoteUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->displayString);
    doParsimUnpacking(b,this->updates);
    doParsimUnpacking(b,this->granularity);
    doParsimUnpacking(b,this->count);
    doParsimUnpacking(b,this->digest);
    doParsimUnpacking(b,this->round);
    doParsimUnpacking(b,this->isPull);
    doParsimUnpacking(b,this->ts);
}

const char * RemoteUpdate::getDisplayString() const
{
    return this->displayString.c_str();
}

void RemoteUpdate::setDisplayString(const char * displayString)
{
    this->displayString = displayString;
}

const char * RemoteUpdate::getUpdates() const
{
    return this->updates.c_str();
}

void RemoteUpdate::setUpdates(const char * updates)
{
    this->updates = updates;
}

int RemoteUpdate::getGranularity() const
{
    return this->granularity;
}

void RemoteUpdate::setGranularity(int granularity)
{
    this->granularity = granularity;
}

int RemoteUpdate::getCount() const
{
    return this->count;
}

void RemoteUpdate::setCount(int count)
{
    this->count = count;
}

const char * RemoteUpdate::getDigest() const
{
    return this->digest.c_str();
}

void RemoteUpdate::setDigest(const char * digest)
{
    this->digest = digest;
}

int RemoteUpdate::getRound() const
{
    return this->round;
}

void RemoteUpdate::setRound(int round)
{
    this->round = round;
}

bool RemoteUpdate::getIsPull() const
{
    return this->isPull;
}

void RemoteUpdate::setIsPull(bool isPull)
{
    this->isPull = isPull;
}

::omnetpp::simtime_t RemoteUpdate::getTs() const
{
    return this->ts;
}

void RemoteUpdate::setTs(::omnetpp::simtime_t ts)
{
    this->ts = ts;
}

class RemoteUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RemoteUpdateDescriptor();
    virtual ~RemoteUpdateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RemoteUpdateDescriptor)

RemoteUpdateDescriptor::RemoteUpdateDescriptor() : omnetpp::cClassDescriptor("RemoteUpdate", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

RemoteUpdateDescriptor::~RemoteUpdateDescriptor()
{
    delete[] propertynames;
}

bool RemoteUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RemoteUpdate *>(obj)!=nullptr;
}

const char **RemoteUpdateDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RemoteUpdateDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RemoteUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int RemoteUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *RemoteUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "displayString",
        "updates",
        "granularity",
        "count",
        "digest",
        "round",
        "isPull",
        "ts",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int RemoteUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "displayString")==0) return base+0;
    if (fieldName[0]=='u' && strcmp(fieldName, "updates")==0) return base+1;
    if (fieldName[0]=='g' && strcmp(fieldName, "granularity")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "count")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "digest")==0) return base+4;
    if (fieldName[0]=='r' && strcmp(fieldName, "round")==0) return base+5;
    if (fieldName[0]=='i' && strcmp(fieldName, "isPull")==0) return base+6;
    if (fieldName[0]=='t' && strcmp(fieldName, "ts")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RemoteUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "int",
        "int",
        "string",
        "int",
        "bool",
        "simtime_t",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **RemoteUpdateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RemoteUpdateDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2:
            if (!strcmp(propertyname,"enum")) return "GranularityType";
            return nullptr;
        default: return nullptr;
    }
}

int RemoteUpdateDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RemoteUpdate *pp = (RemoteUpdate *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RemoteUpdateDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RemoteUpdate *pp = (RemoteUpdate *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RemoteUpdateDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RemoteUpdate *pp = (RemoteUpdate *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDisplayString());
        case 1: return oppstring2string(pp->getUpdates());
        case 2: return enum2string(pp->getGranularity(), "GranularityType");
        case 3: return long2string(pp->getCount());
        case 4: return oppstring2string(pp->getDigest());
        case 5: return long2string(pp->getRound());
        case 6: return bool2string(pp->getIsPull());
        case 7: return simtime2string(pp->getTs());
        default: return "";
    }
}

bool RemoteUpdateDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RemoteUpdate *pp = (RemoteUpdate *)object; (void)pp;
    switch (field) {
        case 0: pp->setDisplayString((value)); return true;
        case 1: pp->setUpdates((value)); return true;
        case 2: pp->setGranularity((GranularityType)string2enum(value, "GranularityType")); return true;
        case 3: pp->setCount(string2long(value)); return true;
        case 4: pp->setDigest((value)); return true;
        case 5: pp->setRound(string2long(value)); return true;
        case 6: pp->setIsPull(string2bool(value)); return true;
        case 7: pp->setTs(string2simtime(value)); return true;
        default: return false;
    }
}

const char *RemoteUpdateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RemoteUpdateDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RemoteUpdate *pp = (RemoteUpdate *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


