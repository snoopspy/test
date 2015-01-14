#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

#include <QComboBox>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

class VObject;

class VTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	VTreeWidget(QWidget *parent, VObject* object);

public:
	VObject* object;

public slots:
	void textEditingFinished();
	void enumCurrentIndexChanged(int index);
	void pbAddClicked();
	void pbDelClicked();
};

class VTreeWidgetItem : public QTreeWidgetItem
{
public:
	VTreeWidgetItem(VTreeWidgetItem *parent, VObject* object, int propIndex);

	VTreeWidget* treeWidget;
	VObject*     object;
	// if propIndex is -1, object means the object itself.
	// otherwise(propIndex is not -1), object means it's parent object.
	int          propIndex;
public:
	virtual const char* name();
};

class VTreeWidgetItemObject : public VTreeWidgetItem
{
public:
	VTreeWidgetItemObject(VTreeWidget* treeWidget, VObject* object); // for root
	VTreeWidgetItemObject(VTreeWidgetItem *parent, VObject* object, bool createDelButton);
	QPushButton* pbDel;
};

class VTreeWidgetItemObjectList : public VTreeWidgetItem
{
public:
	VTreeWidgetItemObjectList(VTreeWidgetItem *parent, VObject* object, int propIndex);
	QPushButton* pbAdd;
};

class VTreeWidgetItemText : public VTreeWidgetItem
{
public:
	VTreeWidgetItemText(VTreeWidgetItem* parent, VObject* object, int propIndex);
	QLineEdit* lineEdit;
};

class VTreeWidgetItemEnum : public VTreeWidgetItem
{
public:
	VTreeWidgetItemEnum(VTreeWidgetItem* parent, VObject* object, int propIndex);
	QComboBox* comboBox;
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H

