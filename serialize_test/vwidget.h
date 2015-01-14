#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

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

public slots:
	void objectNameEditingFinished();
	void textEditingFinished();
	void enumCurrentIndexChanged(int index);
	void pbAddClicked();
	void pbDelClicked();
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

class VTreeWidgetItemPropIndex : public VTreeWidgetItem
{
public:
	VTreeWidgetItemPropIndex(VTreeWidgetItem* parent, VObject* parentObject, int propIndex);

	VObject* object;
	int propIndex;

	virtual QString caption();
	virtual void initialize();
};

class VTreeWidgetItemObjectList : public VTreeWidgetItemPropIndex
{
public:
	VTreeWidgetItemObjectList(VTreeWidgetItem *parent, VObject* object, int propIndex);

	virtual void initialize();
};

class VTreeWidgetItemText : public VTreeWidgetItemPropIndex
{
public:
	VTreeWidgetItemText(VTreeWidgetItem* parent, VObject* object, int propIndex);

	virtual void initialize();
};

class VTreeWidgetItemEnum : public VTreeWidgetItemPropIndex
{
public:
	VTreeWidgetItemEnum(VTreeWidgetItem* parent, VObject* object, int propIndex);

	virtual void initialize();
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H

