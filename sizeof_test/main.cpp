#include <QDebug>

#pragma pack(push, 1)
class Obj {};
class Obj1 : public Obj { char a[1]; };
class Obj2 : public Obj { char a[2]; };
class Obj3 : public Obj { char a[3]; };
class Obj4 : public Obj { char a[4]; };
class Obj5 : public Obj { char a[5]; };
class Obj6 : public Obj { char a[6]; };
class Obj7 : public Obj { char a[7]; };
class Obj8 : public Obj { char a[8]; };
class Obj9 : public Obj { Obj1 obj1; Obj2 obj2; };
#pragma pack(pop)

class VObject  : public QObject {};
class VObject1 : public VObject { char a[1]; };
class VObject2 : public VObject { char a[2]; };
class VObject3 : public VObject { char a[3]; };
class VObject4 : public VObject { char a[4]; };

int main(int argc, char *argv[])
{
	qDebug() << "sizeof(Obj)" << sizeof(Obj);
	qDebug() << "sizeof(Obj1)" << sizeof(Obj1);
	qDebug() << "sizeof(Obj2)" << sizeof(Obj2);
	qDebug() << "sizeof(Obj3)" << sizeof(Obj3);
	qDebug() << "sizeof(Obj4)" << sizeof(Obj4);
	qDebug() << "sizeof(Obj5)" << sizeof(Obj5);
	qDebug() << "sizeof(Obj6)" << sizeof(Obj6);
	qDebug() << "sizeof(Obj7)" << sizeof(Obj7);
	qDebug() << "sizeof(Obj8)" << sizeof(Obj8);
	qDebug() << "sizeof(Obj9)" << sizeof(Obj9);

	qDebug() << "sizeof(QObject)" << sizeof(QObject);
	qDebug() << "sizeof(VObject)" << sizeof(VObject);
	qDebug() << "sizeof(VObject1)" << sizeof(VObject1);
	qDebug() << "sizeof(VObject2)" << sizeof(VObject2);
	qDebug() << "sizeof(VObject3)" << sizeof(VObject3);
	qDebug() << "sizeof(VObject4)" << sizeof(VObject4);

	return 0;
}
