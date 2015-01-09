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
	VTreeWidget(QWidget *parent, VObject* object);

public:
	VObject* object;

public slots:
	void textEditingFinished();
	void enumCurrentIndexChanged(int index);
};

class VTreeWidgetItem : public QTreeWidgetItem
{
public:
	VTreeWidgetItem(VTreeWidget* treeWidget, VTreeWidgetItem *parent, VObject* object, int propIndex) : QTreeWidgetItem(treeWidget, parent)
	{
		if (treeWidget != NULL)
			this->treeWidget = treeWidget;
		else if (parent != NULL)
			this->treeWidget = parent->treeWidget;
		this->object = object;
		this->propIndex = propIndex;
		this->setText(0, getPropName());
		this->setBackground(1, QBrush(QColor(255, 0, 0)));
		//if (parent != NULL)
		//	parent->addChild(this);
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
	VTreeWidgetItemText(VTreeWidget* treeWidget, VTreeWidgetItem* parent, VObject* object, int propIndex);
	QLineEdit* lineEdit;
};

class VTreeWidgetItemEnum : public VTreeWidgetItem
{
public:
	VTreeWidgetItemEnum(VTreeWidget* treeWidget, VTreeWidgetItem* parent, VObject* object, int propIndex);
	QComboBox* comboBox;
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H
