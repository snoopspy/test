#include "vfactory.h"

VFactory::VFactory()
{
}

VFactory::~VFactory()
{
  createMap.clear();
  hierachyMap.clear();
  categoryMap.clear();
}

void VFactory::registerObject(const QMetaObject* mobj)
{
  while (mobj != NULL)
  {
    QString className = mobj->className();
    createMap[className] = mobj;
    mobj = mobj->superClass();
  }
}

void VFactory::registerCategory(QString categoryName, const QMetaObject* mobj)
{
  VMetaObjectList& mobjList = categoryMap[categoryName];
  if (mobjList.indexOf(mobj) == -1)
    mobjList.push_back(mobj);
}

QObject* VFactory::createObject(QString className)
{
  VFactoryCreateMap::iterator it = createMap.find(className);
  if (it == createMap.end())
    return NULL;
  const QMetaObject* mobj = it.value();
  QObject* obj = mobj->newInstance();
  return obj;
}

VMetaObjectList VFactory::findChildsByParentName(QString parentClassName)
{
  VMetaObjectList res;
  for (VFactoryMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (QString(mobj->className()) == parentClassName)
    {
      return it.value();
    }
  }
  return res;
}

VMetaObjectList VFactory::findChildsByAncestorName(QString ancestorClassName)
{
  VMetaObjectList res;
  for (VFactoryMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (isAncestor(mobj, ancestorClassName))
      res += it.value();
  }
  return res;
}

VMetaObjectList VFactory::findChildsByCategoryName(QString categoryName)
{
  VMetaObjectList res;
  for (VFactoryMap::iterator it = categoryMap.begin(); it != categoryMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (QString(mobj->className()) == categoryName)
    {
      return it.value();
    }
  }
  return res;
}

bool VFactory::isAncestor(const QMetaObject* mobj, QString className)
{
  while (mobj != NULL)
  {
    if (QString(mobj->className()) == className)
      return true;
    mobj = mobj->superClass();
  }
  return false;
}

VFactory& VFactory::instance()
{
  static VFactory factory;
  return factory;
}
