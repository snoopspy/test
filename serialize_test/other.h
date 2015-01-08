#ifndef OTHER_H
#define OTHER_H

#include <QList>
#include "vtcpclient.h"
#include "vmac.h"

class NestedClient : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VObject* tcpClient READ getTcpClient)

public:
	VObject* getTcpClient()
	{
		return &tcpClient;
	}
	VTcpClient tcpClient;
};

class VNetInfo : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VIp ip MEMBER ip)
	Q_PROPERTY(VMac mac MEMBER mac)
public:
	VNetInfo() {}

	VIp ip;
	VMac mac;
};

class IntList : public VObject
{
	Q_OBJECT
	Q_PROPERTY(QVariantList intList READ getIntList WRITE setIntList)

public:
	QList<int> intList;
	QVariantList getIntList()
	{
		QVariantList varList;
		foreach (int i, intList)
			varList.push_back(i);
		return varList;
	}
	void setIntList(QVariantList varList)
	{
		intList.clear();
		foreach (QVariant var, varList)
			intList.push_back(var.toInt());
	}
};

class ObjList : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VObjectList objList MEMBER objList)
public:
	VObjectList objList;
};

#endif // OTHER_H
