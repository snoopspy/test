#include <QMetaEnum>
#include <QMetaProperty>
#include "vobject.h"
#include "vwidget.h"

VTreeWidget::VTreeWidget(QWidget *parent, VObject* object) : QTreeWidget(parent)
{
	this->object = object;
	this->setColumnCount(2);
	VTreeWidgetItemObject* root = new VTreeWidgetItemObject(this, object);
	root->setText(0, object->metaObject()->className()); // gilgil temp
	this->insertTopLevelItem(0, root);
	//object->createTreeWidgetItems(root);
}

void VTreeWidget::textEditingFinished()
{
	QLineEdit* lineEdit = (QLineEdit*)this->sender();
	VTreeWidgetItemText* item = (VTreeWidgetItemText*)lineEdit->userData(0);

	QMetaProperty mpro      = item->object->metaObject()->property(item->propIndex);
	const char*   propName  = mpro.name();
	QVariant      propValue = lineEdit->text();
	int           userType  = mpro.userType();

	if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
	{
		QVariant to = VObject::convert(propValue, userType);
		this->object->setProperty(propName, to);
	} else
	{
		item->object->setProperty(propName, propValue);
	}
}

void VTreeWidget::enumCurrentIndexChanged(int index)
{
	Q_UNUSED(index)
	QComboBox* comboBox = (QComboBox*)this->sender();
	VTreeWidgetItemEnum* item = (VTreeWidgetItemEnum*)comboBox->userData(0);
	const char* propName = item->name();
	QVariant propValue = comboBox->currentIndex();
	item->object->setProperty(propName, propValue);
}

VTreeWidgetItem::VTreeWidgetItem(VTreeWidgetItem *parent, VObject* object, int propIndex) : QTreeWidgetItem(parent)
{
	this->treeWidget = parent ? parent->treeWidget : NULL;
	this->object     = object;
	this->propIndex  = propIndex;
	this->setBackground(1, QBrush(QColor(255, 0, 0))); // gilgil temp
	this->setText(0, name());
	if (parent)
		parent->addChild(this);
}

const char* VTreeWidgetItem::name()
{
	if (propIndex == -1)
	{
		const char* name = object->metaObject()->className();
		return name;
	}
	QMetaProperty mpro = object->metaObject()->property(propIndex);
	const char* propName = mpro.name();
	return propName;
}

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidget* treeWidget, VObject* object) : VTreeWidgetItem(NULL, object, -1)
{
	this->treeWidget = treeWidget;
}

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidgetItem *parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object, propIndex)
{
}

VTreeWidgetItemObjectList::VTreeWidgetItemObjectList(VTreeWidgetItem *parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object, propIndex)
{
}

VTreeWidgetItemText::VTreeWidgetItemText(VTreeWidgetItem* parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object, propIndex)
{
	const char* propName = name();
	QVariant variant = object->property(propName);

	lineEdit = new QLineEdit(treeWidget);
	lineEdit->setUserData(0, (QObjectUserData*)this);

	// lineEdit->setFrame(false); // gilgil temp
	lineEdit->setText(variant.toString());
	QObject::connect(lineEdit, SIGNAL(editingFinished()), this->treeWidget, SLOT(textEditingFinished()));

	this->treeWidget->setItemWidget(this, 1, lineEdit);
}

VTreeWidgetItemEnum::VTreeWidgetItemEnum(VTreeWidgetItem* parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object, propIndex)
{
	const char* propName = name();
	QVariant variant = object->property(propName);

	comboBox = new QComboBox(treeWidget);
	comboBox->setUserData(0, (QObjectUserData*)this);

	QMetaProperty mpro = object->metaObject()->property(propIndex);
	QMetaEnum menum = mpro.enumerator();
	int count = menum.keyCount();
	for (int i =  0; i < count; i++)
	{
		QString text = menum.key(i);
		comboBox->insertItem(i, text);
	}
	comboBox->setCurrentIndex(variant.toInt());
	QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), this->treeWidget, SLOT(enumCurrentIndexChanged(int)));

	this->treeWidget->setItemWidget(this, 1, comboBox);
}




