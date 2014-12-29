#include <QDebug>

#include "vvariant.h"

void VVariantUtil::dump(QVariant& variant)
{
	qDebug() << "type()" << variant.type();
	qDebug() << "userType()" << variant.userType();
	qDebug() << "typeName()" << variant.typeName();
	qDebug() << "";
}
