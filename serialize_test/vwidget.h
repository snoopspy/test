#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

#include <QMetaProperty>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class _VObject;
class VObjectList;

// ----------------------------------------------------------------------------
// VTreeWidget
// ----------------------------------------------------------------------------
class VTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	VTreeWidget(QWidget *parent, _VObject* object);

public:
	_VObject* object;
};

// ----------------------------------------------------------------------------
// VTreeWidgetItem
// ----------------------------------------------------------------------------
class VTreeWidgetItem : public QTreeWidgetItem
{
public:
	VTreeWidgetItem(VTreeWidgetItem *parent);

	VTreeWidget* treeWidget;

	virtual QString caption() = 0;
	virtual void initialize();
};

// ----------------------------------------------------------------------------
// VTreeWidgetItemProperty
// ----------------------------------------------------------------------------
class VTreeWidgetItemProperty : public VTreeWidgetItem
{
public:
  VTreeWidgetItemProperty(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro);

	_VObject* object;
  QMetaProperty mpro;

	virtual QString caption();
	virtual void initialize();
};

// ----------------------------------------------------------------------------
// VTreeWidgetItemStr
// ----------------------------------------------------------------------------
class VTreeWidgetItemStr : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemStr(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro);

	virtual void initialize();
};

// ----------------------------------------------------------------------------
// VTreeWidgetItemBool
// ----------------------------------------------------------------------------
class VTreeWidgetItemBool : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemBool(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro);

  virtual void initialize();
};

// ----------------------------------------------------------------------------
// VTreeWidgetItemEnum
// ----------------------------------------------------------------------------
class VTreeWidgetItemEnum : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemEnum(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro);

	virtual void initialize();
};

// ----------------------------------------------------------------------------
// VTreeWidgetItemObject
// ----------------------------------------------------------------------------
class VTreeWidgetItemObject : public VTreeWidgetItem
{
public:
  typedef enum {
    SHOW_OBJECT_NAME,
    SHOW_DEL_BUTTON
  } Type;
public:
  VTreeWidgetItemObject(VTreeWidget* treeWidget, _VObject* object); // for root _VObject
  VTreeWidgetItemObject(VTreeWidgetItem* parent, _VObject* object, Type type);

  _VObject* object;
  Type type;

  virtual QString caption();
  virtual void initialize();
};

// ----------------------------------------------------------------------------
// VTreeWidgetItemObjectList
// ----------------------------------------------------------------------------
class VTreeWidgetItemObjectList : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemObjectList(VTreeWidgetItem *parent, _VObject* object, QMetaProperty mpro);

  virtual void initialize();
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H

