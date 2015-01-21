#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

#include <QMetaProperty>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class VObject;
class VObjectList;

class VTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	VTreeWidget(QWidget *parent, VObject* object);

public:
	VObject* object;
};

class VTreeWidgetItem : public QTreeWidgetItem
{
public:
	VTreeWidgetItem(VTreeWidgetItem *parent);

	VTreeWidget* treeWidget;

	virtual QString caption() = 0;
	virtual void initialize();
};

class VTreeWidgetItemObject : public VTreeWidgetItem
{
public:
	typedef enum {
		SHOW_OBJECT_NAME,
		SHOW_DEL_BUTTON
	} Type;
public:
	VTreeWidgetItemObject(VTreeWidget* treeWidget, VObject* object); // for root VObject
	VTreeWidgetItemObject(VTreeWidgetItem* parent, VObject* object, Type type);

	VObject* object;
	Type type;

	virtual QString caption();
	virtual void initialize();
};

class VTreeWidgetItemProperty : public VTreeWidgetItem
{
public:
  VTreeWidgetItemProperty(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);

	VObject* object;
  QMetaProperty mpro;

	virtual QString caption();
	virtual void initialize();
};

class VTreeWidgetItemObjectList : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemObjectList(VTreeWidgetItem *parent, VObject* object, QMetaProperty mpro);

	virtual void initialize();
};

class VTreeWidgetItemText : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemText(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);

	virtual void initialize();
};

class VTreeWidgetItemEnum : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemEnum(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);

	virtual void initialize();
};

class VTreeWidgetItemBool : public VTreeWidgetItemProperty
{
public:
  VTreeWidgetItemBool(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);

  virtual void initialize();
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H

