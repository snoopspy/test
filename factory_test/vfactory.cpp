#include "vfactory.h"

VFactory::VFactory()
{

}

VFactory::~VFactory()
{
  classMap.clear();
  hierachyMap.clear();
  categoryMap.clear();
}

void VFactory::registerObject(const QMetaObject* mobj)
{
  while (mobj != NULL)
  {
    QString className = mobj->className();
    classMap[className] = mobj;
    mobj = mobj->superClass();
  }
}

void VFactory::registerCategory(QString categoryName, const QMetaObject* mobj)
{
  categoryMap[categoryName] = mobj;
}

QObject* VFactory::createObject(QString className)
{
  VFactoryMap::iterator it = classMap.find(className);
  if (it == classMap.end())
    return NULL;
  const QMetaObject* mobj = it.value();
  QObject* obj = mobj->newInstance();
  return obj;
}

VFactoryList VFactory::findChildsByParentName(QString parentClassName)
{
  VFactoryList res;
  for (VFactoryMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    QString className = it.key();
    if (className == parentClassName)
    {
      const QMetaObject* mobj = it.value();
      res.push_back(mobj);
    }
  }
  return res;
}

VFactoryList VFactory::findChildsByAncestorName(QString ancestorClassName)
{
  VFactoryList res;
  for (VFactoryMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    QString className = it.key();
    const QMetaObject* mobj = it.value();
    if (isAncestor(mobj, ancestorClassName))
      res.push_back(mobj);
  }
  return res;
}

VFactoryList VFactory::findChildsByCategoryName(QString categoryName)
{
  VFactoryList res;
  for (VFactoryMap::iterator it = categoryMap.begin(); it != categoryMap.end(); it++)
  {
    QString className = it.key();
    if (className == categoryName)
    {
      const QMetaObject* mobj = it.value();
      res.push_back(mobj);
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
