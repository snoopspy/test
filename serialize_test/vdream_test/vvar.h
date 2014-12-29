#ifndef VVAR_H
#define VVAR_H

#include <QVariant>

#define V_QVAR_CONVERSION(TYPE) \
	TYPE(QVariant variant) { *this = qvariant_cast<TYPE>(variant); } \
	operator QVariant() { return QVariant::fromValue<TYPE>(*this); }

#define V_TYPE_CONVERSION(TYPE, NEWTYPE, MEMBER) \
	TYPE(NEWTYPE newType) { MEMBER = newType; } \
	operator NEWTYPE() { return MEMBER; } \

#define V_PROPERTY_FUNC(TYPE, NAME, GET, SET, MEMBER) \
	TYPE GET() { return MEMBER; } \
	void SET(TYPE GET) { MEMBER = GET; }

#endif // VVAR_H
