#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "vserializable.h"
#include "vstrrep.h" // gilgil temp 2015.01.07

bool VSerializable::loadFromFile(QString fileName, const QMetaObject* mobj)
{
	VRep strRep;
	if (!strRep.loadFromFile(fileName))
	{
		return false;
	}

	VRep rep;
	if (mobj == NULL)
	{
		rep = strRep;
	} else
	{
		rep = VStrRep::strReptoRep(strRep, mobj);
	}
	this->load(rep);
	return true;
}

bool VSerializable::saveToFile(QString fileName, const QMetaObject* mobj)
{
	VRep rep;
	this->save(rep);
	VRep strRep;
	if (mobj == NULL)
	{
		strRep = rep;
	} else
	{
		strRep = VStrRep::repToStrRep(rep, mobj);
	}
	return strRep.saveToFile(fileName);
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

#ifdef GTEST
#include <gtest/gtest.h>

class Obj : public VSerializable
{
public:
	int i;
	QString s;

	virtual void load(VRep& rep)
	{
		i = rep["i"].toInt();
		s = rep["s"].toString();
	}

	virtual void save(VRep& rep)
	{
		rep["i"] = i;
		rep["s"] = s;
	}
};

TEST(SerializeTest, objTest)
{
	Obj obj;
	obj.i = 999;
	obj.s = "hello";
	obj.saveToFile("test.json", NULL);
	{
		Obj newObj;
		newObj.loadFromFile("test.json", NULL);
		qDebug() << newObj.i;
		qDebug() << newObj.s;
	}
}


#endif // GTEST
