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
	VTcpClient tcpClient;
public:
	VObject* getTcpClient()
	{
		return &tcpClient;
	}
};

class VNetInfo : public VObject
{
	Q_OBJECT
  Q_PROPERTY(VIp ip MEMBER ip)
  Q_PROPERTY(VMac mac MEMBER mac)
public:
	// VNetInfo() {}

	VIp ip;
	VMac mac;
};

class IntList : public VObject
{
	Q_OBJECT
  Q_PROPERTY(QVariantList intList READ getIntList WRITE setIntList)

public:
	QList<int> intList;

public:
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

typedef _VObjectList<VTcpClient> VTcpClientList;
class ObjList : public VObject
{
	Q_OBJECT
  Q_PROPERTY(bool enabled MEMBER enabled)
	Q_PROPERTY(VObjectList* tcpClientList READ getTcpClientList)

public:
  bool enabled;
	VTcpClientList tcpClientList;

public:
  ObjList() : VObject(NULL) { enabled = true; }
	VObjectList* getTcpClientList() { return &tcpClientList; }
};

#endif // OTHER_H
