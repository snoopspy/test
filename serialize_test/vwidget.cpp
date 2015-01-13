#include <assert.h>
#include <QMetaEnum>
#include <QMetaProperty>
#include <QHBoxLayout>
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
	VTreeWidgetItemObject* root = new VTreeWidgetItemObject(this, object, true);
	root->setText(0, object->metaObject()->className()); // gilgil temp
	this->insertTopLevelItem(0, root);
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
	const char* propName = item->name();
	QVariant propValue = comboBox->currentIndex();
	item->object->setProperty(propName, propValue);
}

void VTreeWidget::pbAddClicked()
{
	QPushButton* pbAdd = dynamic_cast<QPushButton*>(sender());
	assert(pbAdd != NULL);
	VTreeWidgetItemObjectList* item = (VTreeWidgetItemObjectList*)(pbAdd->userData(0));
	assert(item != NULL);
	VObjectList* childObjectList = item->object->property(item->name()).value<VObjectList*>();
	assert(childObjectList != NULL);

	VObject* newObject = childObjectList->createObject();
	VTreeWidgetItem* childItem = new VTreeWidgetItem(item, newObject, -1);
	newObject->createTreeWidgetItems(childItem);
	childItem->setExpanded(true);
}

void VTreeWidget::pbDelClicked()
{
	QPushButton* pbDel = dynamic_cast<QPushButton*>(sender());
	assert(pbDel != NULL);
	VTreeWidgetItemObjectList* item = (VTreeWidgetItemObjectList*)(pbDel->userData(0));
	assert(item != NULL);
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
}

VTreeWidgetItem::VTreeWidgetItem(VTreeWidgetItem *parent, VObject* object, int propIndex) : QTreeWidgetItem(parent)
{
	this->treeWidget = parent ? parent->treeWidget : NULL;
	this->object     = object;
	this->propIndex  = propIndex;
	this->setBackground(1, QBrush(QColor(128, 128, 128))); // gilgil temp
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

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidget* treeWidget, VObject* object, bool showObjectName) : VTreeWidgetItem(NULL, object, -1)
{
	this->treeWidget = treeWidget;
	if (!showObjectName) hideObjectName();
}

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidgetItem *parent, VObject* object, int propIndex, bool showObjectName) : VTreeWidgetItem(parent, object, propIndex)
{
	if (!showObjectName) hideObjectName();
}

void VTreeWidgetItemObject::hideObjectName()
{

}

VTreeWidgetItemObjectList::VTreeWidgetItemObjectList(VTreeWidgetItem *parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object, propIndex)
{
	VTreeWidget* treeWidget = (VTreeWidget*)parent->treeWidget;
	pbAdd = new QPushButton(treeWidget);
	pbAdd->setText("+");
	pbAdd->setUserData(0, (QObjectUserData*)this);
	pbDel = new QPushButton(treeWidget);
	pbDel->setText("-");
	pbDel->setUserData(0, (QObjectUserData*)this);

	QWidget* container = new QWidget(treeWidget);
	QHBoxLayout* layout = new QHBoxLayout(container);
	container->setLayout(layout);
	layout->addWidget(pbAdd);
	layout->addWidget(pbDel);

	parent->treeWidget->setItemWidget(this, 1, container);
	QObject::connect(pbAdd, SIGNAL(clicked()), treeWidget, SLOT(pbAddClicked()));
	QObject::connect(pbDel, SIGNAL(clicked()), treeWidget, SLOT(pbDelClicked()));
}

VTreeWidgetItemText::VTreeWidgetItemText(VTreeWidgetItem* parent, VObject* object, int propIndex) : VTreeWidgetItem(parent, object, propIndex)
{
	const char* propName = name();
	QVariant variant = object->property(propName);

	lineEdit = new QLineEdit(treeWidget);
	lineEdit->setUserData(0, (QObjectUserData*)this);

	//lineEdit->setFrame(false); // gilgil temp
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




