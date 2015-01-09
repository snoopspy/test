#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>
#include "vserializable.h"
#include "vwidget.h"

class VObject : public QObject, public VSerializable
{
	Q_OBJECT

public:
	VObject(VObject* parent = 0) : QObject(parent) {}
	VObject(const VObject& rhs) : QObject(0) { Q_UNUSED(rhs) }
	virtual ~VObject() {}

public:
	virtual void load(VRep& rep);
	virtual void save(VRep& rep);

public:
	bool loadFromFile(QString fileName);
	bool saveToFile(QString fileName);

#ifdef QT_GUI_LIB
public:
	virtual QList<VTreeWidgetItem*> createTreeWidgetItems(VTreeWidget* treeWidget, VTreeWidgetItem* parentItem);
#endif // QT_GUI_LIB
};
//Q_DECLARE_METATYPE(VObject)
Q_DECLARE_METATYPE(VObject*)

class VObjectList : public QList<VObject*>
{
public:
	virtual VObject* createObject() { return new VObject; }
	virtual ~VObjectList() {}
};
//Q_DECLARE_METATYPE(VObjectList)
Q_DECLARE_METATYPE(VObjectList*)

template <class T>
class _VObjectList : public VObjectList
{
	virtual VObject* createObject() { return new T; }
};

#endif // VOBJECT_H
