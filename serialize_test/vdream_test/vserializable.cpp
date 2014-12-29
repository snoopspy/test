#include "vserializable.h"

VRep& operator >> (VRep& rep, VSerializable& serializable)
{
	serializable.load(rep);
	return rep;
}

VRep& operator << (VRep& rep, VSerializable& serializable)
{
	serializable.save(rep);
	return rep;
}
