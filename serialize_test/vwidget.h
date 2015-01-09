#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

#include <QComboBox>
#include <QHeaderView>
#include <QLineEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

class VObject;

class VTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	VTreeWidget(QWidget *parent, VObject* object) : QTreeWidget(parent)
	{
		this->object = object;
		this->setColumnCount(2);
	}

public:
	VObject* object;

public slots:
	void textEditingFinished();
	void enumCurrentIndexChanged(int index);
};

class VTreeWidgetItem : public QTreeWidgetItem
{
public:
	VTreeWidgetItem(VTreeWidget *parent, int propIndex) : QTreeWidgetItem(parent)
	{
		this->treeWidget = parent;
		this->object = parent->object;
		this->propIndex = propIndex;
		this->setText(0, getPropName());
	}
	VTreeWidget* treeWidget;
	VObject* object;
	int propIndex;

public:
	const char* getPropName();
};

class VTreeWidgetItemText : public VTreeWidgetItem
{
public:
	VTreeWidgetItemText(VTreeWidget *parent, int propIndex);
	QLineEdit* lineEdit;
};

class VTreeWidgetItemEnum : public VTreeWidgetItem
{
public:
	VTreeWidgetItemEnum(VTreeWidget *parent, int propIndex);
	QComboBox* comboBox;
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H
