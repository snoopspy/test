#include <assert.h>
#include <QDebug>
#include <QMetaEnum>
#include <QMetaObject>
#include <QMetaProperty>

#ifdef QT_GUI_LIB
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#endif // QT_GUI_LIB

#include "vmetadump.h"
#include "vobject.h"
#include "vwidget.h"

bool VObject::loadFromFile(QString fileName)
{
	VRep rep;
	if (!rep.loadFromFile(fileName))
		return false;
	this->load(rep);
	return true;
}

bool VObject::saveToFile(QString fileName)
{
	VRep rep;
	this->save(rep);
	return rep.saveToFile(fileName);
}

QVariant VObject::convert(QVariant from, int type)
{
	QVariant to(type, NULL);

	void* fromData     = from.data();
	int   fromUserType = from.userType();
	void* toData       = to.data();
	int   toUserType   = to.userType();
	bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
	if (!res)
	{
		printf("VObject::load QMetaType::convert return false\n");
		VMetaDump::dump(&from); // gilgil temp 2015.01.07
		VMetaDump::dump(&to); // gilgil temp 2015.01.07
	}
	return to;
}

void VObject::load(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int count = mobj->propertyCount();
	for (int propIndex = 0; propIndex < count; propIndex++)
	{
		QMetaProperty mpro      = mobj->property(propIndex);
		const char*   propName  = mpro.name();
		QVariant      propValue = rep[propName];
		int           userType  = mpro.userType();

		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = this->property(propName).value<VObject*>();
			VRep     childRep = rep[propName].toMap();
			childObj->load(childRep);
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
			VObjectList* childObjectList = this->property(propName).value<VObjectList*>();
			VRep childRepList = rep[propName].toMap();
			for (VRep::iterator it = childRepList.begin(); it != childRepList.end(); it++)
			{
				VRep childRep = it->toMap();
				VObject* vobj = childObjectList->createObject();
				vobj->load(childRep);
				childObjectList->push_back(vobj);
			}
		} else
		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			QString   key   = propValue.toString();
			QVariant  to    = menum.keyToValue(qPrintable(key));
			this->setProperty(propName, to);
		} else
		if (QMetaType::hasRegisteredConverterFunction(QVariant::String, userType))
		{
			QVariant to = convert(propValue, userType);
			this->setProperty(propName, to);
		} else
		{
			this->setProperty(propName, propValue);
		}
	}
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int count = mobj->propertyCount();
	for (int propIndex = 0; propIndex < count; propIndex++)
	{
		QMetaProperty mpro      = mobj->property(propIndex);
		const char*   propName  = mpro.name();
		QVariant      propValue = this->property(propName);
		int           userType  = mpro.userType();

		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = this->property(propName).value<VObject*>();
			VRep     childRep;
			childObj->save(childRep);
			rep[propName] = childRep;
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
			VObjectList* childObjectList = this->property(propName).value<VObjectList*>();
			VRep childRepList;
			int i = 0;
			foreach (VObject* childObj, *childObjectList)
			{
				VRep childRep;
				childObj->save(childRep);
				childRepList[QString::number(i)] = childRep;
				i++;
			}
			rep[propName] = childRepList;
		} else
		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			int       index = propValue.toInt();
			QString   to    = menum.key(index);
			rep[propName] = to;
		} else
		if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
		{
			QVariant to = convert(propValue, QVariant::String);
			rep[propName] = to;
		} else
		{
			if (!(QString(propName) == "objectName" && propValue == ""))
				rep[propName] = propValue;
		}
	}
}

#ifdef QT_GUI_LIB
QWidget* VObject::createWidget(QWidget* parent)
{
  VTreeWidget* treeWidget = new VTreeWidget(parent, this);
  return treeWidget;
}

void VObject::createTreeWidgetItems(VTreeWidgetItem* parent)
{
  const QMetaObject *mobj = this->metaObject();
  int count = this->metaObject()->propertyCount();

  for (int propIndex = 0; propIndex < count; propIndex++)
  {
    QMetaProperty mpro     = mobj->property(propIndex);
    const char*   propName = mpro.name();
    int           userType = mpro.userType();

    if (QString(propName) == "objectName") continue;

    if (userType == qMetaTypeId<VObject*>())
    {
      VObject* childObj = this->property(propName).value<VObject*>();
      VTreeWidgetItemObject* item = new VTreeWidgetItemObject(parent, childObj, VTreeWidgetItemObject::SHOW_OBJECT_NAME);
      item->initialize();
      childObj->createTreeWidgetItems(item);
    } else
    if (userType == qMetaTypeId<VObjectList*>())
    {
      VObjectList* childObjectList = this->property(propName).value<VObjectList*>();
      VTreeWidgetItemObjectList* item = new VTreeWidgetItemObjectList(parent, this, mpro);
      item->initialize();

      foreach (VObject* childObj, *childObjectList)
      {
        VTreeWidgetItemObject* childItem = new VTreeWidgetItemObject(item, childObj, VTreeWidgetItemObject::SHOW_DEL_BUTTON);
        childItem->initialize();
        childObj->createTreeWidgetItems(childItem);
      }
    } else
    if (mpro.isEnumType())
    {
      VTreeWidgetItemEnum* item = new VTreeWidgetItemEnum(parent, this, mpro);
      item->initialize();
    } else
    if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
    {
      VTreeWidgetItemText* item = new VTreeWidgetItemText(parent, this, mpro);
      item->initialize();
    } else
    {
      VTreeWidgetItemText* item = new VTreeWidgetItemText(parent, this, mpro);
      item->initialize();
    }
  }
}

void VObject::objectNameEditingFinished()
{
  QLineEdit* lineEdit = (QLineEdit*)this->sender();
  assert(lineEdit != NULL);

  VTreeWidgetItemObject* item = (VTreeWidgetItemObject*)(qvariant_cast<void*>(lineEdit->property("_treeWidgetItem")));
  assert(item != NULL);

  VObject* object = item->object;
  assert(object != NULL);

  object->setObjectName(lineEdit->text());
}

void VObject::textEditingFinished()
{
  QLineEdit* lineEdit = (QLineEdit*)this->sender();
  assert(lineEdit != NULL);

  VTreeWidgetItemText* item = (VTreeWidgetItemText*)(qvariant_cast<void*>(lineEdit->property("_treeWidgetItem")));
  assert(item != NULL);

  QMetaProperty mpro      = item->mpro;
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

void VObject::enumCurrentIndexChanged(int index)
{
  QComboBox* comboBox = (QComboBox*)this->sender();
  assert(comboBox != NULL);
  VTreeWidgetItemEnum* item = (VTreeWidgetItemEnum*)(qvariant_cast<void*>(comboBox->property("_treeWidgetItem")));
  assert(item != NULL);

  QString propName = item->caption();
  QVariant propValue = index;
  item->object->setProperty(qPrintable(propName), propValue);
}

void VObject::pbAddClicked()
{
  QPushButton* pbAdd = dynamic_cast<QPushButton*>(sender());
  assert(pbAdd != NULL);

  VTreeWidgetItemObjectList* item = (VTreeWidgetItemObjectList*)(qvariant_cast<void*>(pbAdd->property("_treeWidgetItem")));
  assert(item != NULL);

  VObject* object = item->object;
  assert(object != NULL);

  QMetaProperty mpro = item->mpro;
  QVariant variant = object->property(mpro.name());
  VObjectList* objectList = variant.value<VObjectList*>();
  assert(objectList != NULL);

  VObject* newObject = objectList->createObject();
  VTreeWidgetItemObject* childItem = new VTreeWidgetItemObject(item, newObject, VTreeWidgetItemObject::SHOW_DEL_BUTTON);
  childItem->initialize();
  newObject->createTreeWidgetItems(childItem);
}

void VObject::pbDelClicked()
{
  QPushButton* pbDel = dynamic_cast<QPushButton*>(sender());
  assert(pbDel != NULL);

  VTreeWidgetItemObject* item = (VTreeWidgetItemObject*)qvariant_cast<void*>(pbDel->property("_treeWidgetItem"));
  assert(item != NULL);

  VObject* delObject = item->object;
  assert(delObject != NULL);

  VTreeWidgetItemObjectList* parentItem = dynamic_cast<VTreeWidgetItemObjectList*>(item->parent());
  assert(parentItem != NULL);

  VObject* object = parentItem->object;
  assert(object != NULL);

  QMetaProperty mpro = parentItem->mpro;

  QVariant variant = object->property(mpro.name());
  VObjectList* objectList = variant.value<VObjectList*>();
  assert(objectList != NULL);

  objectList->removeOne(delObject);
  parentItem->removeChild(item);
}

#endif // QT_GUI_LIB
