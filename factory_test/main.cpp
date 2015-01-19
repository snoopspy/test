#include <stdio.h>
#include <QMetaObject>
#include "obj1.h"
#include "vfactory.h"

void test()
{
  Obj111 _obj111;

  VFactory f;
  f.registerObject(_obj111.metaObject());

  QObject* obj = dynamic_cast<QObject*>(f.createObject("Obj11"));
  printf("%s\n", obj->metaObject()->className());
}

int main()
{
  test();
}
