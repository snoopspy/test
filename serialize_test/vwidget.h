#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

#include <QDebug>
#include <QLineEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

typedef QWidget     VWidget;

class VObject;
class VTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	VTreeWidget(QWidget *parent, VObject* object);
	virtual ~VTreeWidget() {}
public:
	VObject* object;
public slots:
	void editingFinished();
	void textChanged(const QString &s);
};

class VTreeWidgetItem : public QTreeWidgetItem
{
public:
	VTreeWidgetItem(VTreeWidget *parent, QString propName) : QTreeWidgetItem(parent)
	{
		this->treeWidget = parent;
		this->object = parent->object;
		this->propName = propName;
	}
	//virtual ~VTreeWidgetItem() {}
	VTreeWidget* treeWidget;
	VObject* object;
	QString propName;
};

class VTreeWidgetLineEditItem : public VTreeWidgetItem
{
public:
	VTreeWidgetLineEditItem(VTreeWidget *parent, QString propName) : VTreeWidgetItem(parent, propName)
	{
		lineEdit = new QLineEdit(parent);
		lineEdit->setFrame(false);
		lineEdit->setUserData(0, (QObjectUserData*)this);
		QObject::connect(lineEdit, SIGNAL(editingFinished()), treeWidget, SLOT(editingFinished()));
		//QObject::connect(lineEdit, SIGNAL(textChanged(const QString &)), treeWidget, SLOT(textChanged(const QString &)));
		treeWidget->setItemWidget(this, 1, lineEdit);
	}
	//virtual ~VTreeWidgetLineEditItem() {}
	QLineEdit* lineEdit;
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H
