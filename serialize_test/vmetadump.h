#ifndef VMETADUMP_H
#define VMETADUMP_H

#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QVariant>

/*
#define V_QVAR_CONVERSION(TYPE) \
	TYPE(QVariant variant) { *this = qvariant_cast<TYPE>(variant); } \
	operator QVariant() { return QVariant::fromValue<TYPE>(*this); }

#define V_TYPE_CONVERSION(TYPE, NEWTYPE, MEMBER) \
	TYPE(NEWTYPE newType) { MEMBER = newType; } \
	operator NEWTYPE() { return MEMBER; } \

#define V_PROPERTY_FUNC(TYPE, GET, SET, MEMBER) \
	TYPE GET() { return MEMBER; } \
	void SET(TYPE GET) { MEMBER = GET; }
*/

class VMetaDump
{
public:
	static void dump(QVariant* var);
	static void dump(QObject* obj, int ident = 0);
	static void dump(QMetaObject* mobj, QObject* obj = NULL, int ident = 0);
	static void dump(QMetaProperty *mpro, QObject* obj = NULL, int ident = 0);
	// static void dump(QMetaEnum *menum, QObject* obj = NULL, int ident = 0); // gilgil temp 2015.01.06
protected:
	static QString duplicate(char ch, int count);
};

#endif // VMETADUMP_H
