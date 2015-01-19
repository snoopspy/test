#ifndef OBJ1_H
#define OBJ1_H

#include <QObject>

class Obj1 : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj1() : QObject(NULL)
  {

  }
};

class Obj11 : public Obj1
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj11()
  {

  }
};

class Obj111 : public Obj11
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj111()
  {

  }
};


#endif // OBJ1_H
