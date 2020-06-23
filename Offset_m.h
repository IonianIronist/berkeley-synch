//
// Generated file, do not edit! Created by nedtool 5.6 from Offset.msg.
//

#ifndef __OFFSET_M_H
#define __OFFSET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>Offset.msg:1</tt> by nedtool.
 * <pre>
 * message Offset
 * {
 *     int id[];
 *     double offset[];
 * }
 * </pre>
 */
class Offset : public ::omnetpp::cMessage
{
  protected:
    int *id; // array ptr
    unsigned int id_arraysize;
    double *offset; // array ptr
    unsigned int offset_arraysize;

  private:
    void copy(const Offset& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Offset&);

  public:
    Offset(const char *name=nullptr, short kind=0);
    Offset(const Offset& other);
    virtual ~Offset();
    Offset& operator=(const Offset& other);
    virtual Offset *dup() const override {return new Offset(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setIdArraySize(unsigned int size);
    virtual unsigned int getIdArraySize() const;
    virtual int getId(unsigned int k) const;
    virtual void setId(unsigned int k, int id);
    virtual void setOffsetArraySize(unsigned int size);
    virtual unsigned int getOffsetArraySize() const;
    virtual double getOffset(unsigned int k) const;
    virtual void setOffset(unsigned int k, double offset);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Offset& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Offset& obj) {obj.parsimUnpack(b);}


#endif // ifndef __OFFSET_M_H

