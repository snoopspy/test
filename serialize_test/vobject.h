#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>

#include "vserializable.h"

class VObject : public QObject, public VSerializable
{
	Q_OBJECT

public:
	VObject(VObject* parent = 0) : QObject(parent) {}
	virtual ~VObject() {}

public:
	virtual void load(VRep& rep);
	virtual void save(VRep& rep);

public:
	bool loadFromFile(QString fileName);
	bool saveToFile(QString fileName);
};

#endif // VOBJECT_H
