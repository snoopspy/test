#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "vserializable.h"

bool VSerializable::loadFromFile(QString fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	QByteArray ba = file.readAll();
	file.close();

	QJsonDocument jdoc = QJsonDocument::fromJson(ba);

	QJsonObject jobj = jdoc.object();

	VRep rep = jobj.toVariantMap();
	rep >> *this;

	return true;
}

bool VSerializable::saveToFile(QString fileName)
{
	VRep rep;
	rep << *this;

	QJsonObject jobj = QJsonObject::fromVariantMap(rep);

	QJsonDocument jdoc;
	jdoc.setObject(jobj);

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
		return false;

	file.write(jdoc.toJson());
	file.close();

	return true;
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
#include "vtcpclient.h"

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
	obj.saveToFile("test.json");
	{
		Obj newObj;
		newObj.loadFromFile("test.json");
		qDebug() << newObj.i;
		qDebug() << newObj.s;
	}
}


#endif // GTEST
