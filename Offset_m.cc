//
// Generated file, do not edit! Created by nedtool 5.6 from Offset.msg.
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
#include "Offset_m.h"

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

Register_Class(Offset)

Offset::Offset(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    id_arraysize = 0;
    this->id = 0;
    offset_arraysize = 0;
    this->offset = 0;
}

Offset::Offset(const Offset& other) : ::omnetpp::cMessage(other)
{
    id_arraysize = 0;
    this->id = 0;
    offset_arraysize = 0;
    this->offset = 0;
    copy(other);
}

Offset::~Offset()
{
    delete [] this->id;
    delete [] this->offset;
}

Offset& Offset::operator=(const Offset& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Offset::copy(const Offset& other)
{
    delete [] this->id;
    this->id = (other.id_arraysize==0) ? nullptr : new int[other.id_arraysize];
    id_arraysize = other.id_arraysize;
    for (unsigned int i=0; i<id_arraysize; i++)
        this->id[i] = other.id[i];
    delete [] this->offset;
    this->offset = (other.offset_arraysize==0) ? nullptr : new double[other.offset_arraysize];
    offset_arraysize = other.offset_arraysize;
    for (unsigned int i=0; i<offset_arraysize; i++)
        this->offset[i] = other.offset[i];
}

void Offset::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    b->pack(id_arraysize);
    doParsimArrayPacking(b,this->id,id_arraysize);
    b->pack(offset_arraysize);
    doParsimArrayPacking(b,this->offset,offset_arraysize);
}

void Offset::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    delete [] this->id;
    b->unpack(id_arraysize);
    if (id_arraysize==0) {
        this->id = 0;
    } else {
        this->id = new int[id_arraysize];
        doParsimArrayUnpacking(b,this->id,id_arraysize);
    }
    delete [] this->offset;
    b->unpack(offset_arraysize);
    if (offset_arraysize==0) {
        this->offset = 0;
    } else {
        this->offset = new double[offset_arraysize];
        doParsimArrayUnpacking(b,this->offset,offset_arraysize);
    }
}

void Offset::setIdArraySize(unsigned int size)
{
    int *id2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = id_arraysize < size ? id_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        id2[i] = this->id[i];
    for (unsigned int i=sz; i<size; i++)
        id2[i] = 0;
    id_arraysize = size;
    delete [] this->id;
    this->id = id2;
}

unsigned int Offset::getIdArraySize() const
{
    return id_arraysize;
}

int Offset::getId(unsigned int k) const
{
    if (k>=id_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", id_arraysize, k);
    return this->id[k];
}

void Offset::setId(unsigned int k, int id)
{
    if (k>=id_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", id_arraysize, k);
    this->id[k] = id;
}

void Offset::setOffsetArraySize(unsigned int size)
{
    double *offset2 = (size==0) ? nullptr : new double[size];
    unsigned int sz = offset_arraysize < size ? offset_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        offset2[i] = this->offset[i];
    for (unsigned int i=sz; i<size; i++)
        offset2[i] = 0;
    offset_arraysize = size;
    delete [] this->offset;
    this->offset = offset2;
}

unsigned int Offset::getOffsetArraySize() const
{
    return offset_arraysize;
}

double Offset::getOffset(unsigned int k) const
{
    if (k>=offset_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", offset_arraysize, k);
    return this->offset[k];
}

void Offset::setOffset(unsigned int k, double offset)
{
    if (k>=offset_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", offset_arraysize, k);
    this->offset[k] = offset;
}

class OffsetDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    OffsetDescriptor();
    virtual ~OffsetDescriptor();

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

Register_ClassDescriptor(OffsetDescriptor)

OffsetDescriptor::OffsetDescriptor() : omnetpp::cClassDescriptor("Offset", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

OffsetDescriptor::~OffsetDescriptor()
{
    delete[] propertynames;
}

bool OffsetDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Offset *>(obj)!=nullptr;
}

const char **OffsetDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *OffsetDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int OffsetDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int OffsetDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *OffsetDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
        "offset",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int OffsetDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "offset")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *OffsetDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **OffsetDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *OffsetDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int OffsetDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Offset *pp = (Offset *)object; (void)pp;
    switch (field) {
        case 0: return pp->getIdArraySize();
        case 1: return pp->getOffsetArraySize();
        default: return 0;
    }
}

const char *OffsetDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Offset *pp = (Offset *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OffsetDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Offset *pp = (Offset *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getId(i));
        case 1: return double2string(pp->getOffset(i));
        default: return "";
    }
}

bool OffsetDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Offset *pp = (Offset *)object; (void)pp;
    switch (field) {
        case 0: pp->setId(i,string2long(value)); return true;
        case 1: pp->setOffset(i,string2double(value)); return true;
        default: return false;
    }
}

const char *OffsetDescriptor::getFieldStructName(int field) const
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

void *OffsetDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Offset *pp = (Offset *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


