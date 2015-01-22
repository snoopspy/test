#ifndef OTHER_H
#define OTHER_H

#include <QList>
#include "vtcpclient.h"
#include "vmac.h"

class NestedClient : public _VObject
{
	Q_OBJECT
	Q_PROPERTY(_VObject* tcpClient READ getTcpClient)

public:
	_VTcpClient tcpClient;
public:
	_VObject* getTcpClient()
	{
		return &tcpClient;
	}
};

class VNetInfo : public _VObject
{
	Q_OBJECT
  Q_PROPERTY(_VIp ip MEMBER ip)
  Q_PROPERTY(_VMac mac MEMBER mac)
public:
	// VNetInfo() {}

	_VIp ip;
	_VMac mac;
};

class IntList : public _VObject
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

typedef _VObjectList<_VTcpClient> VTcpClientList;
class ObjList : public _VObject
{
	Q_OBJECT
  Q_PROPERTY(bool enabled MEMBER enabled)
	Q_PROPERTY(VObjectList* tcpClientList READ getTcpClientList)

public:
  bool enabled;
	VTcpClientList tcpClientList;

public:
  ObjList() : _VObject(NULL) { enabled = true; }
	VObjectList* getTcpClientList() { return &tcpClientList; }
};

#endif // OTHER_H
