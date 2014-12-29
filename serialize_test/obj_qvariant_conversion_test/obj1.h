#ifndef OBJ1_H
#define OBJ1_H

#include "obj.h"

class Obj1 : public Obj
{
	V_QVARIANT_CONVERSION(Obj1)
	V_TYPE_CONVERSION(Obj1, int, m_i)
public:
	Obj1() {}
	Obj1(const Obj1& rhs) : Obj() { m_i = rhs.m_i; }

	//Obj1(int i)     { m_i = i; }
	//operator int() { return m_i; }

	//Obj1(QVariant variant) { *this = qvariant_cast<Obj1>(variant); }
	//operator QVariant()   { return QVariant::fromValue<Obj1>(*this); }

private:
	int m_i;
};
Q_DECLARE_METATYPE(Obj1)

#endif // OBJ1_H
