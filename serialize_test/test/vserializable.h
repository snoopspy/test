#ifndef VSERIALIZABLE_H
#define VSERIALIZABLE_H

#include "vvar.h"

class VSerializable
{
public:
    virtual void load(VVar& var);
    virtual void save(VVar& var);
};

VVar& operator << (VVar& var, VSerializable& serializable);
VVar& operator >> (VVar& var, VSerializable& serializable);

#endif // VSERIALIZABLE_H
