#include <assert.h>
#include <QDebug>
#include <QMetaEnum>
#include <QMetaObject>
#include <QMetaProperty>

#ifdef QT_GUI_LIB
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#endif // QT_GUI_LIB

#include "vmetadump.h"
#include "vobject.h"
#include "vserializer.h"
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

void VObject::load(VRep& rep)
{
  const QMetaObject *mobj = this->metaObject();
  int count = mobj->propertyCount();
  VSerializerMgr& mgr = VSerializerMgr::instance();

  for (int propIndex = 0; propIndex < count; propIndex++)
  {
    QMetaProperty mpro = mobj->property(propIndex);
    if (!mgr.load(this, mpro, rep))
    {
      printf("mgr.load return false\n");
      break;
    }
  }
}

void VObject::save(VRep& rep)
{
  const QMetaObject *mobj = this->metaObject();
  int count = mobj->propertyCount();
  VSerializerMgr& mgr = VSerializerMgr::instance();

  for (int propIndex = 0; propIndex < count; propIndex++)
  {
    QMetaProperty mpro = mobj->property(propIndex);
    if (!mgr.save(this, mpro, rep))
    {
      printf("mgr.save return false\n");
      break;
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
  VSerializerMgr& mgr = VSerializerMgr::instance();

  for (int propIndex = 0; propIndex < count; propIndex++)
  {
    QMetaProperty mpro = mobj->property(propIndex);
    const char* propName = mpro.name();
    if (QString(propName) == "objectName") continue;
    if (!mgr.createTreeWidgetItems(parent, this, mpro))
    {
      printf("mgr.save return false\n");
      break;
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

  VTreeWidgetItemStr* item = (VTreeWidgetItemStr*)(qvariant_cast<void*>(lineEdit->property("_treeWidgetItem")));
  assert(item != NULL);

  QMetaProperty mpro      = item->mpro;
  const char*   propName  = mpro.name();
  QVariant      propValue = lineEdit->text();
  int           userType  = mpro.userType();

  if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
  {
    QVariant to = VConvertSerializer::convert(propValue, userType);
    item->object->setProperty(propName, to);
  } else
  {
    item->object->setProperty(propName, propValue);
  }
}

void VObject::boolStateChanged(int state)
{
  QCheckBox* checkBox = (QCheckBox*)this->sender();
  assert(checkBox != NULL);
  VTreeWidgetItemBool* item = (VTreeWidgetItemBool*)(qvariant_cast<void*>(checkBox->property("_treeWidgetItem")));
  assert(item != NULL);

  QString propName = item->caption();
  bool propValue = state == Qt::Checked;
  item->object->setProperty(qPrintable(propName), propValue);
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
