#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>
#include "vserializable.h"
#include "vwidget.h"

class VObject : public QObject, public VSerializable
{
  Q_OBJECT

  friend class VTreeWidget;

public:
  VObject(VObject* parent = 0) : QObject(parent) {}
  VObject(const VObject& rhs) : QObject(0) { Q_UNUSED(rhs) }
  virtual ~VObject() {}

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
Q_DECLARE_METATYPE(VObject*)

class VObjectList : public QList<VObject*>
{
public:
  virtual VObject* createObject() { return new VObject; }
  virtual ~VObjectList() {}
};
Q_DECLARE_METATYPE(VObjectList*)

template <class T>
class _VObjectList : public VObjectList
{
public:
  virtual VObject* createObject() { return new T; }
};

#endif // VOBJECT_H
