#include "vserializable.h"

#include <stdio.h>

void VSerializable::load(VVar& var)
{
    Q_UNUSED(var)
    fprintf(stderr, "[%s:%d] %s virtual function call\n", __FILE__, __LINE__, __func__);
}

void VSerializable::save(VVar& var)
{
    Q_UNUSED(var)
    fprintf(stderr, "[%s:%d] %s virtual function call\n", __FILE__, __LINE__, __func__);
}

VVar& operator << (VVar& var, VSerializable& serializable)
{
    serializable.save(var);
    return var;
}

VVar& operator >> (VVar& var, VSerializable& serializable)
{
    serializable.load(var);
    return var;
}
