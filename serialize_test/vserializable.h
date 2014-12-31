#ifndef VSERIALIZABLE_H
#define VSERIALIZABLE_H

#include "vrep.h"

class VSerializable
{
public:
	virtual void load(VRep& rep) = 0;
	virtual void save(VRep& rep) = 0;
};

VRep& operator >> (VRep& rep, VSerializable& serializable);
VRep& operator << (VRep& rep, VSerializable& serializable);

#endif // VSERIALIZABLE_H
