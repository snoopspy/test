#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "vserializable.h"
#include "vstrrep.h" // gilgil temp 2015.01.07

bool VSerializable::loadFromFile(QString fileName, const QMetaObject* mobj)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	QByteArray ba = file.readAll();
	file.close();

	QJsonDocument jdoc = QJsonDocument::fromJson(ba);

	QJsonObject jobj = jdoc.object();

	VRep strRep = jobj.toVariantMap();
	if (mobj == NULL)
	{
		this->load(strRep);
	} else
	{
		VRep rep = VStrRep::toRep(strRep, mobj);
		this->load(rep);
	}

	return true;
}

bool VSerializable::saveToFile(QString fileName, const QMetaObject* mobj)
{
	VRep rep;
	this->save(rep);
	if (mobj != NULL)
	{
		VRep strRep = VStrRep::toStrRep(rep, mobj);
		rep = strRep;
	}

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
