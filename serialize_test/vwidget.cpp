#include <assert.h>

#include <QComboBox>
#include <QLineEdit>
#include <QMetaEnum>
#include <QMetaProperty>
#include <QPushButton>

#include "vobject.h"
#include "vwidget.h"

VTreeWidget::VTreeWidget(QWidget *parent, VObject* object) : QTreeWidget(parent)
{
	this->object = object;
	this->setColumnCount(2);
	QStringList sList; sList << "property" << "value";
	this->setHeaderLabels(sList);
	// this->setStyleSheet("QTreeWidget::item{ height: 50px}"); // gilgil temp
	// this->setIndentation(6); // gilgil temp
	VTreeWidgetItemObject* root = new VTreeWidgetItemObject(this, object);
	this->insertTopLevelItem(0, root);
	root->initialize();
	object->createTreeWidgetItems(root);
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
		item->object->setProperty(propName, to);
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
	QString propName = item->caption();
	QVariant propValue = comboBox->currentIndex();
	item->object->setProperty(qPrintable(propName), propValue);
}

void VTreeWidget::pbAddClicked()
{
	QPushButton* pbAdd = dynamic_cast<QPushButton*>(sender());
	assert(pbAdd != NULL);
	VTreeWidgetItemObjectList* item = (VTreeWidgetItemObjectList*)(pbAdd->userData(0));
	assert(item != NULL);
	VObjectList* childObjectList = dynamic_cast<VObjectList*>(object);
	assert(childObjectList != NULL);

	VObject* newObject = childObjectList->createObject();
	VTreeWidgetItemObject* childItem = new VTreeWidgetItemObject(item, newObject, VTreeWidgetItemObject::SHOW_DEL_BUTTON);
	childItem->initialize();
	newObject->createTreeWidgetItems(childItem);
	childItem->setExpanded(true);
}

void VTreeWidget::pbDelClicked()
{
	QPushButton* pbDel = dynamic_cast<QPushButton*>(sender());
	assert(pbDel != NULL);
	VTreeWidgetItemObject* item = (VTreeWidgetItemObject*)(pbDel->userData(0));
	assert(item != NULL);
	VTreeWidgetItemObjectList* parentItem = dynamic_cast<VTreeWidgetItemObjectList*>(item->parent());
	assert(parentItem != NULL);
	VObjectList* objectList = dynamic_cast<VObjectList*>(parentItem->object);
	assert(objectList != NULL);
	bool res = objectList->removeOne(item->object);
	assert(res == true);
	//parentItem->removeChild(item);
	/*
	VObjectList* childObjectList = item->object->property(item->name()).value<VObjectList*>();
	assert(childObjectList != NULL);

	QList<QTreeWidgetItem*> selectedItems = item->treeWidget->selectedItems();
	foreach (QTreeWidgetItem* selectedItem, selectedItems)
	{
		VTreeWidgetItem* _selectedItem = (VTreeWidgetItem*)selectedItem;
		if (_selectedItem->parent() == item)
		{
			childObjectList->removeAll(_selectedItem->object);
			item->removeChild(selectedItem);
		}
	}
	*/
}

VTreeWidgetItem::VTreeWidgetItem(VTreeWidgetItem *parent, VObject* object) : QTreeWidgetItem(parent)
{
	if (parent)
		this->treeWidget = parent->treeWidget;
	else
		this->treeWidget = NULL;
	this->object = object;
}

QString VTreeWidgetItem::caption()
{
	return QString(object->metaObject()->className());
}

void VTreeWidgetItem::initialize()
{
	this->setText(0, caption());
	this->setBackground(1, QBrush(QColor(128, 128, 128))); // gilgil temp 2015.01.14
	if (parent())
		parent()->addChild(this);
}

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidget* treeWidget, VObject* object) : VTreeWidgetItem(NULL, object)
{
	this->treeWidget = treeWidget;
	this->type = SHOW_OBJECT_NAME;
}

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidgetItem *parent, VObject* object, Type type) : VTreeWidgetItem(parent, object)
{
	this->type = type;
}

void VTreeWidgetItemObject::initialize()
{
	VTreeWidgetItem::initialize();

	if (type == SHOW_OBJECT_NAME) {
		QLineEdit* leObjectName = new QLineEdit(treeWidget);
		leObjectName->setUserData(0, (QObjectUserData*)this);
		leObjectName->setText(object->objectName());
		treeWidget->setItemWidget(this, 1, leObjectName);
	} else
	if (type == SHOW_DEL_BUTTON)
	{
		QPushButton* pbDel = new QPushButton(treeWidget);
		pbDel->setUserData(0, (QObjectUserData*)this);
		pbDel->setText("-");
		QObject::connect(pbDel, SIGNAL(clicked()), treeWidget, SLOT(pbDelClicked()));
		treeWidget->setItemWidget(this, 1, pbDel);
	}
}

VTreeWidgetItemObjectList::VTreeWidgetItemObjectList(VTreeWidgetItem *parent, VObject* object) : VTreeWidgetItem(parent, object)
{
}

void VTreeWidgetItemObjectList::initialize()
{
	VTreeWidgetItem::initialize();

	QPushButton* pbAdd = new QPushButton(treeWidget);
	pbAdd->setUserData(0, (QObjectUserData*)this);
	pbAdd->setText("+");
	QObject::connect(pbAdd, SIGNAL(clicked()), treeWidget, SLOT(pbAddClicked()));
	treeWidget->setItemWidget(this, 1, pbAdd);
}

VTreeWidgetItemPropIndex::VTreeWidgetItemPropIndex(VTreeWidgetItem* parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object)
{
	this->propIndex = propIndex;
}

QString VTreeWidgetItemPropIndex::caption()
{
	QMetaProperty mpro = object->metaObject()->property(propIndex);
	const char* propName = mpro.name();
	return QString(propName);
}

void VTreeWidgetItemPropIndex::initialize()
{
	VTreeWidgetItem::initialize();
}

VTreeWidgetItemText::VTreeWidgetItemText(VTreeWidgetItem* parent, VObject* object, int propIndex) : VTreeWidgetItemPropIndex(parent, object, propIndex)
{
}

void VTreeWidgetItemText::initialize()
{
	VTreeWidgetItemPropIndex::initialize();

	QString propName = caption();
	QVariant variant = object->property(qPrintable(propName));

	QLineEdit* lineEdit = new QLineEdit(treeWidget);
	lineEdit->setUserData(0, (QObjectUserData*)this);
	lineEdit->setText(variant.toString());
	//lineEdit->setFrame(false); // gilgil temp
	QObject::connect(lineEdit, SIGNAL(editingFinished()), this->treeWidget, SLOT(textEditingFinished()));
	this->treeWidget->setItemWidget(this, 1, lineEdit);
}

VTreeWidgetItemEnum::VTreeWidgetItemEnum(VTreeWidgetItem* parent, VObject* object, int propIndex) : VTreeWidgetItemPropIndex(parent, object, propIndex)
{
}

void VTreeWidgetItemEnum::initialize()
{
	VTreeWidgetItemPropIndex::initialize();

	QString propName = caption();
	QVariant variant = object->property(qPrintable(propName));

	QComboBox* comboBox = new QComboBox(treeWidget);
	comboBox->setUserData(0, (QObjectUserData*)this);
	//comboBox->setFrame(false); // gilgil temp

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


