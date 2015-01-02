#include <QFile>

#include "vserializable.h"

bool VSerializable::loadFromFile(QString fileName)
{

	VRep rep;
	rep >> *this;
	return true;
}

bool VSerializable::saveToFile(QString fileName)
{
	QFile file(fileName);
	file.open(QIODevice::ReadOnly)
	file.error();
}

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
