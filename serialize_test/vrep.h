#ifndef VREP_H
#define VREP_H

#include <QVariantMap>

class VRep : public QVariantMap
{
public:
	VRep() {}
	VRep(const QVariantMap& rhs) { *(QVariantMap*)this = rhs; }

public:
	bool loadFromFile(QString fileName);
	bool saveToFile(QString fileName);
};

//typedef QVariantMap VRep; // gilgil temp 2015.01.07

#endif // VREP_H
