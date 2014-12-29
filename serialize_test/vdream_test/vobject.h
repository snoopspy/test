#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>

#include "vserializable.h"

class VObject : public QObject, public VSerializable
{
	Q_OBJECT

public:
	VObject() {}
	virtual ~VObject() {}

public:
	virtual void load(VRep& rep);
	virtual void save(VRep& rep);
};

#endif // VOBJECT_H
