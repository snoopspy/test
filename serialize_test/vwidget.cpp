#include <QDebug>
#include <QMetaEnum>
#include <QMetaProperty>
#include "vobject.h"
#include "vwidget.h"

void VTreeWidget::textEditingFinished()
{
	QLineEdit* lineEdit = (QLineEdit*)this->sender();
	VTreeWidgetItemText* item = (VTreeWidgetItemText*)lineEdit->userData(0);

	QMetaProperty mpro     = item->object->metaObject()->property(item->propIndex);
	const char*   propName = mpro.name();
	QVariant      from     = lineEdit->text();
	int           userType = mpro.userType();

	if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
	{
		QVariant to(userType, NULL);
		void* fromData     = from.data();
		int   fromUserType = from.userType(); // QVariant::String
		void* toData       = to.data();
		int   toUserType   = to.userType();
		bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
		if (!res)
		{
			printf("VObject::save QMetaType::convert return false name=%s\n", propName); // gilgil temp 2015.01.07
		}
		this->object->setProperty(propName, to);
	} else
	{
		item->object->setProperty(propName, from);
	}
}

void VTreeWidget::enumCurrentIndexChanged(int index)
{
	Q_UNUSED(index)
	QComboBox* comboBox = (QComboBox*)this->sender();
	VTreeWidgetItemEnum* item = (VTreeWidgetItemEnum*)comboBox->userData(0);
	const char* propName = item->getPropName();
	QVariant propValue = comboBox->currentIndex();
	item->object->setProperty(propName, propValue);
}

const char* VTreeWidgetItem::getPropName()
{
	QMetaProperty mpro = object->metaObject()->property(propIndex);
	const char* propName = mpro.name();
	return propName;
}

VTreeWidgetItemText::VTreeWidgetItemText(VTreeWidget *parent, int propIndex) : VTreeWidgetItem(parent, propIndex)
{
	const char* propName = getPropName();
	QVariant variant = object->property(propName);

	lineEdit = new QLineEdit(parent);
	lineEdit->setUserData(0, (QObjectUserData*)this);

	lineEdit->setFrame(false);
	lineEdit->setText(variant.toString());
	QObject::connect(lineEdit, SIGNAL(editingFinished()), treeWidget, SLOT(textEditingFinished()));

	treeWidget->setItemWidget(this, 1, lineEdit);
}

VTreeWidgetItemEnum::VTreeWidgetItemEnum(VTreeWidget *parent, int propIndex) : VTreeWidgetItem(parent, propIndex)
{
	const char* propName = getPropName();
	QVariant variant = object->property(propName);

	comboBox = new QComboBox(parent);
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
	QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), treeWidget, SLOT(enumCurrentIndexChanged(int)));

	treeWidget->setItemWidget(this, 1, comboBox);
}
