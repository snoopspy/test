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
	QJsonDocument doc;

	doc = QJsonDocument::fromJson(ba);
	file.close();
	qDebug() << doc.toBinaryData();

	QJsonObject obj;
	obj = doc.object();
	qDebug() << obj.count();

	VRep rep;
	rep = obj.toVariantMap();

	rep >> *this;

	return true;
}

bool VSerializable::saveToFile(QString fileName)
{
	VRep rep;
	rep << *this;

	QJsonObject obj;
	obj = QJsonObject::fromVariantMap(rep);

	QJsonDocument doc;
	doc.setObject(obj);
	qDebug() << doc.toJson(); // gilgil temp 2015.01.03

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
		return false;

	file.write(doc.toJson());
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

TEST(SerializeTest, tcpClientTest)
{
	VTcpClient tcpClient;
	tcpClient.ip = 1234;
	tcpClient.port = 80;
	tcpClient.saveToFile("tcpClient.json");
	{
		VTcpClient newTcpClient;
		newTcpClient.loadFromFile("tcpClient.json");
		qDebug() << (quint32)newTcpClient.ip;
		qDebug() << newTcpClient.port;
	}
}

#endif // GTEST
