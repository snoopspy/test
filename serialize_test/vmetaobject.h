#ifndef VVARIANT_H
#define VVARIANT_H

#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QVariant>

#define V_QVAR_CONVERSION(TYPE) \
	TYPE(QVariant variant) { *this = qvariant_cast<TYPE>(variant); } \
	operator QVariant() { return QVariant::fromValue<TYPE>(*this); }

#define V_TYPE_CONVERSION(TYPE, NEWTYPE, MEMBER) \
	TYPE(NEWTYPE newType) { MEMBER = newType; } \
	operator NEWTYPE() { return MEMBER; } \

#define V_PROPERTY_FUNC(TYPE, GET, SET, MEMBER) \
	TYPE GET() { return MEMBER; } \
	void SET(TYPE GET) { MEMBER = GET; }

class VMetaObject
{
public:
	static void dump(QObject* obj);
	static void dump(QMetaObject* mobj);
	static void dump(QMetaProperty *mpro);
	static void dump(QMetaEnum *menum);
};

#endif // VVARIANT_H
