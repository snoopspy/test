#ifndef VVARIANT_H
#define VVARIANT_H

#include <QVariant>

#define V_QVARIANT_CONVERSION(TYPE) \
public: \
	TYPE(QVariant variant) { *this = qvariant_cast<TYPE>(variant); } \
	operator QVariant() { return QVariant::fromValue<TYPE>(*this); }

#define V_TYPE_CONVERSION(TYPE, NEWTYPE, MEMBER) \
public: \
	TYPE(NEWTYPE newType) { MEMBER = newType; } \
	operator NEWTYPE() { return (NEWTYPE)MEMBER; }

class VVariantUtil
{
public:
	static void dump(QVariant& variant);
};

#endif // VVARIANT_H
