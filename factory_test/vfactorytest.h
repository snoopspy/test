#ifndef VFACTORYTEST_H
#define VFACTORYTEST_H

#ifdef GTEST
#include <gtest/gtest.h>
#include <QObject>

class Obj : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj() {}
};

class Obj1 : public Obj
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj1() {}
};

class Obj2 : public Obj
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj2() {}
};

class Obj3 : public Obj
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj3() {}
};

class Obj31 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj31() {}
};

class Obj32 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj32() {}
};

class Obj33 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj33() {}
};

class Obj34 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj34() {}
};

#endif // GTEST

#endif // VFACTORYTEST_H

