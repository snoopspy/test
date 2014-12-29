#ifndef OBJ2_H
#define OBJ2_H

#include "obj.h"

class Obj2 : public Obj
{
	V_QVARIANT_CONVERSION(Obj2)
public:
	Obj2() {}
	Obj2(const Obj2& rhs) : Obj() { m_i = rhs.m_i; }

	Obj2(int i)     { m_i = i; }
	operator int() { return m_i; }

	//Obj2(QVariant variant) { *this = qvariant_cast<Obj2>(variant); }
	//operator QVariant()   { return QVariant::fromValue<Obj2>(*this); }

private:
	int m_i;
};
Q_DECLARE_METATYPE(Obj2)

#endif // OBJ2_H
