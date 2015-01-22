#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>
#include "vserializable.h"
#include "vwidget.h"

class _VObject : public QObject, public VSerializable
{
	Q_OBJECT

	friend class VTreeWidget;

public:
  _VObject(_VObject* parent = 0) : QObject(parent) {}
  _VObject(const _VObject& rhs) : QObject(0) { Q_UNUSED(rhs) }
  virtual ~_VObject() {}

public:
	bool loadFromFile(QString fileName);
	bool saveToFile(QString fileName);

public:
	virtual void load(VRep& rep);
	virtual void save(VRep& rep);

#ifdef QT_GUI_LIB
public:
  virtual QWidget* createWidget(QWidget* parent);
  virtual void createTreeWidgetItems(VTreeWidgetItem* parent);

public slots:
  void objectNameEditingFinished();
  void textEditingFinished();
  void boolStateChanged(int state);
  void enumCurrentIndexChanged(int index);
  void pbAddClicked();
  void pbDelClicked();
#endif // QT_GUI_LIB
};
Q_DECLARE_METATYPE(_VObject*)

class VObjectList : public QList<_VObject*>
{
public:
  virtual _VObject* createObject() { return new _VObject; }
	virtual ~VObjectList() {}
};
Q_DECLARE_METATYPE(VObjectList*)

template <class T>
class _VObjectList : public VObjectList
{
  virtual _VObject* createObject() { return new T; }
};

#endif // VOBJECT_H
