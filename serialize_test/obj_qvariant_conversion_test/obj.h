#ifndef OBJ_H
#define OBJ_H

#include <QDebug>
#include <QMetaType>

#include "vvariant.h"

class Obj
{
	V_QVARIANT_CONVERSION(Obj)
public:
	Obj() { qDebug() << "Obj::Obj"; }

	//Obj(QVariant variant) { *this = qvariant_cast<Obj>(variant); }
	//operator QVariant()   { return QVariant::fromValue<Obj>(*this); }
};
Q_DECLARE_METATYPE(Obj)

#endif // OBJ_H
