#ifndef VFACTORY_H
#define VFACTORY_H

#include <QList>
#include <QMap>
#include <QMetaObject>
#include <QString>

typedef QMap<QString, const QMetaObject*> VFactoryMap;
typedef QList<const QMetaObject*> VFactoryList;

class VFactory
{
  VFactoryMap classMap;    /* by className */
  VFactoryMap hierachyMap; /* by parentClassName */
  VFactoryMap categoryMap; /* by categoryName */

public:
  VFactory();
  virtual ~VFactory();

  void registerObject(const QMetaObject* mobj);
  void registerCategory(QString categoryName, const QMetaObject* mobj);

  QObject* createObject(QString className);

  VFactoryList findChildsByParentName(QString parentClassName);
  VFactoryList findChildsByAncestorName(QString ancestorClassName);
  VFactoryList findChildsByCategoryName(QString categoryName);

protected:
  static bool isAncestor(const QMetaObject* mobj, QString className);
};

#endif // VFACTORY_H
