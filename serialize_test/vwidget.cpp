#include <assert.h>

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QMetaEnum>
#include <QPushButton>

#include "vobject.h"
#include "vwidget.h"

// ----------------------------------------------------------------------------
// VTreeWidget
// ----------------------------------------------------------------------------
VTreeWidget::VTreeWidget(QWidget *parent, _VObject* object) : QTreeWidget(parent)
{
  this->object = object;
  this->setColumnCount(2);
  QStringList sList; sList << "property" << "value";
  this->setHeaderLabels(sList);
  // this->setStyleSheet("QTreeWidget::item{ height: 50px}"); // by gilgil
  // this->setIndentation(6); // by gilgil
  VTreeWidgetItemObject* root = new VTreeWidgetItemObject(this, object);
  this->insertTopLevelItem(0, root);
  root->initialize();
  object->createTreeWidgetItems(root);
}

// ----------------------------------------------------------------------------
// VTreeWidgetItem
// ----------------------------------------------------------------------------
VTreeWidgetItem::VTreeWidgetItem(VTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
  if (parent)
    this->treeWidget = parent->treeWidget;
  else
    this->treeWidget = NULL;
}

void VTreeWidgetItem::initialize()
{
  this->setText(0, caption());
  //this->setBackground(1, QBrush(QColor(128, 128, 128))); // gilgil temp 2015.01.14
  if (parent())
    parent()->addChild(this);
  setExpanded(true);
}

// ----------------------------------------------------------------------------
// VTreeWidgetItemProperty
// ----------------------------------------------------------------------------
VTreeWidgetItemProperty::VTreeWidgetItemProperty(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro) : VTreeWidgetItem(parent)
{
  this->object = object;
  this->mpro = mpro;
}

QString VTreeWidgetItemProperty::caption()
{
  const char* propName = mpro.name();
  return QString(propName);
}

void VTreeWidgetItemProperty::initialize()
{
  VTreeWidgetItem::initialize();
}

// ----------------------------------------------------------------------------
// VTreeWidgetItemStr
// ----------------------------------------------------------------------------
VTreeWidgetItemStr::VTreeWidgetItemStr(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro) : VTreeWidgetItemProperty(parent, object, mpro)
{
}

void VTreeWidgetItemStr::initialize()
{
  VTreeWidgetItemProperty::initialize();

  QString propName = caption();
  QVariant variant = object->property(qPrintable(propName));

  QLineEdit* lineEdit = new QLineEdit(treeWidget);
  lineEdit->setProperty("_treeWidgetItem", QVariant::fromValue<void*>((void*)this));
  lineEdit->setText(variant.toString());
  lineEdit->setFrame(false);
  QObject::connect(lineEdit, SIGNAL(editingFinished()), object, SLOT(textEditingFinished()));
  this->treeWidget->setItemWidget(this, 1, lineEdit);
}

// ----------------------------------------------------------------------------
// VTreeWidgetItemBool
// ----------------------------------------------------------------------------
VTreeWidgetItemBool::VTreeWidgetItemBool(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro) : VTreeWidgetItemProperty(parent, object, mpro)
{
}

void VTreeWidgetItemBool::initialize()
{
  VTreeWidgetItemProperty::initialize();

  QString propName = caption();
  QVariant variant = object->property(qPrintable(propName));

  QCheckBox* checkBox = new QCheckBox(treeWidget);
  checkBox->setProperty("_treeWidgetItem", QVariant::fromValue<void*>((void*)this));

  checkBox->setChecked(variant.toBool());
  QObject::connect(checkBox, SIGNAL(stateChanged(int)), object, SLOT(boolStateChanged(int)));

  this->treeWidget->setItemWidget(this, 1, checkBox);
}

// ----------------------------------------------------------------------------
// VTreeWidgetItemEnum
// ----------------------------------------------------------------------------
VTreeWidgetItemEnum::VTreeWidgetItemEnum(VTreeWidgetItem* parent, _VObject* object, QMetaProperty mpro) : VTreeWidgetItemProperty(parent, object, mpro)
{
}

void VTreeWidgetItemEnum::initialize()
{
  VTreeWidgetItemProperty::initialize();

  QString propName = caption();
  QVariant variant = object->property(qPrintable(propName));

  QComboBox* comboBox = new QComboBox(treeWidget);
  comboBox->setProperty("_treeWidgetItem", QVariant::fromValue<void*>((void*)this));
  comboBox->setFrame(false);

  QMetaEnum menum = mpro.enumerator();
  int count = menum.keyCount();
  for (int i =  0; i < count; i++)
  {
    QString text = menum.key(i);
    comboBox->insertItem(i, text);
  }
  comboBox->setCurrentIndex(variant.toInt());
  QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), object, SLOT(enumCurrentIndexChanged(int)));

  this->treeWidget->setItemWidget(this, 1, comboBox);
}

// ----------------------------------------------------------------------------
// VTreeWidgetItemObject
// ----------------------------------------------------------------------------
VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidget* treeWidget, _VObject* object) : VTreeWidgetItem(NULL)
{
  this->treeWidget = treeWidget;
  this->object = object;
  this->type = SHOW_OBJECT_NAME;
}

VTreeWidgetItemObject::VTreeWidgetItemObject(VTreeWidgetItem *parent, _VObject* object, Type type) : VTreeWidgetItem(parent)
{
  this->object = object;
  this->type = type;
}

QString VTreeWidgetItemObject::caption()
{
  return QString(object->metaObject()->className());
}

void VTreeWidgetItemObject::initialize()
{
  VTreeWidgetItem::initialize();

  if (type == SHOW_OBJECT_NAME) {
    QLineEdit* leObjectName = new QLineEdit(treeWidget);
    leObjectName->setProperty("_treeWidgetItem", QVariant::fromValue<void*>((void*)this));
    leObjectName->setText(object->objectName());
    leObjectName->setFrame(false);
    QObject::connect(leObjectName, SIGNAL(editingFinished()), object, SLOT(objectNameEditingFinished()));
    treeWidget->setItemWidget(this, 1, leObjectName);
  } else
  if (type == SHOW_DEL_BUTTON)
  {
    QPushButton* pbDel = new QPushButton(treeWidget);
    pbDel->setProperty("_treeWidgetItem", QVariant::fromValue<void*>((void*)this));
    pbDel->setText("-");
    QObject::connect(pbDel, SIGNAL(clicked()), object, SLOT(pbDelClicked()));
    treeWidget->setItemWidget(this, 1, pbDel);
  }
}

// ----------------------------------------------------------------------------
// VTreeWidgetItemObjectList
// ----------------------------------------------------------------------------
VTreeWidgetItemObjectList::VTreeWidgetItemObjectList(VTreeWidgetItem *parent, _VObject* object, QMetaProperty mpro) : VTreeWidgetItemProperty(parent, object, mpro)
{
}

void VTreeWidgetItemObjectList::initialize()
{
  VTreeWidgetItemProperty::initialize();

  QPushButton* pbAdd = new QPushButton(treeWidget);
  pbAdd->setProperty("_treeWidgetItem", QVariant::fromValue<void*>((void*)this));
  pbAdd->setText("+");
  QObject::connect(pbAdd, SIGNAL(clicked()), object, SLOT(pbAddClicked()));
  treeWidget->setItemWidget(this, 1, pbAdd);
}
