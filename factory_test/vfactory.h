#ifndef VFACTORY_H
#define VFACTORY_H

#include <QList>
#include <QMap>
#include <QMetaObject>
#include <QString>

typedef QMap<QString, const QMetaObject*> VFactoryCreateMap;
typedef QList<const QMetaObject*> VMetaObjectList;
typedef QMap<const QMetaObject*, VMetaObjectList> VFactoryMap;

class VFactory
{
protected:
  VFactoryCreateMap createMap;   /* by class name */
  VFactoryMap       hierachyMap; /* by parent class */
  VFactoryMap       categoryMap; /* by category class */

public:
  VFactory();
  virtual ~VFactory();

public:
  void registerObject(const QMetaObject* mobj);
  void registerCategory(QString categoryName, const QMetaObject* mobj);

  QObject* createObject(QString className);

  VMetaObjectList findChildsByParentName(QString parentClassName);
  VMetaObjectList findChildsByAncestorName(QString ancestorClassName);
  VMetaObjectList findChildsByCategoryName(QString categoryName);

protected:
  static bool isAncestor(const QMetaObject* mobj, QString className);

public:
  static VFactory& instance();

private:
  Q_DISABLE_COPY(VFactory)
};

#endif // VFACTORY_H
