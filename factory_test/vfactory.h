#ifndef VFACTORY_H
#define VFACTORY_H

#include <QList>
#include <QMap>
#include <QMetaObject>
#include <QString>

class VFactory
{
public:
  typedef QList<const QMetaObject*>                    VMetaObjectList;
  typedef QMap<QString,            const QMetaObject*> VCreateMap;
  typedef QMap<const QMetaObject*, VMetaObjectList>    VHierachyMap;
  typedef QMap<QString,            VMetaObjectList>    VCategoryMap;

  VCreateMap   createMap;
  VHierachyMap hierachyMap;
  VCategoryMap categoryMap;

public:
  VFactory();
  virtual ~VFactory();

  void registerObject(const QMetaObject* mobj);
  void registerCategory(QString categoryName, const QMetaObject* mobj);
  QObject* createObject(QString className);

  VMetaObjectList getChildsByParentClassName(QString parentClassName);
  VMetaObjectList getChildsByAncestorClassName(QString ancestorClassName);
  VMetaObjectList getChildsByCategoryName(QString categoryName);

protected:
  static bool isAncestor(const QMetaObject* mobj, QString className);

public:
  static VFactory& instance();
};

#endif // VFACTORY_H
