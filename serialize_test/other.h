#ifndef OTHER_H
#define OTHER_H

#include <QList>
#include "vtcpclient.h"
#include "vmac.h"

class NestedClient : public VObject
{
	Q_OBJECT

public:
	VTcpClient tcpClient;

public:
	Q_PROPERTY(VObject* tcpClient READ getTcpClient)
	VObject* getTcpClient()
	{
		return &tcpClient;
	}
};

class VNetInfo : public VObject
{
	Q_OBJECT
public:
	// VNetInfo() {}

	VIp ip;
	VMac mac;

public:
	Q_PROPERTY(VIp ip MEMBER ip)
	Q_PROPERTY(VMac mac MEMBER mac)
};

class IntList : public VObject
{
	Q_OBJECT

public:
	QList<int> intList;

public:
	Q_PROPERTY(QVariantList intList READ getIntList WRITE setIntList)
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

//typedef _VObjectList<VTcpClient> VTcpClientList;
class VTcpClientList : public VObjectList
{
	virtual VObject* createObject() { return new VTcpClient; }
};

class ObjList : public VObject
{
	Q_OBJECT
public:
	VTcpClientList tcpClientList;

public:
	Q_PROPERTY(VObjectList* tcpClientList READ getTcpClientList)
	VObjectList* getTcpClientList() { return &tcpClientList; }
};

#endif // OTHER_H
