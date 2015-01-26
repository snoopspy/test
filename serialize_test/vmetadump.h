#ifndef VMETADUMP_H
#define VMETADUMP_H

#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QVariant>

class VMetaDump
{
public:
  static void dump(QVariant* var);
  static void dump(QObject* obj, int ident = 0);
  static void dump(QMetaObject* mobj, QObject* obj = NULL, int ident = 0);
  static void dump(QMetaProperty *mpro, QObject* obj = NULL, int ident = 0);
protected:
  static QString duplicate(char ch, int count);
};

#endif // VMETADUMP_H
