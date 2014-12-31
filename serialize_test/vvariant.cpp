#include <QDebug>
#include "vvariant.h"

void VVariant::dump(QObject* obj)
{
	QString objectName = obj->objectName();
	dump((QMetaObject*)obj->metaObject());
}

void VVariant::dump(QMetaObject* mobj)
{
	const char* className = mobj->className();
	int propertyCount = mobj->propertyCount();
	qDebug() << "className" << className << "propertyCount" << propertyCount;
	for (int i = 0; i < propertyCount; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		dump(&mpro);
	}
}

void VVariant::dump(QMetaProperty *mpro)
{
	const char* name = mpro->name();
	qDebug() << name;
	if (mpro->isEnumType())
	{
		qDebug() << "enum type";
		int keyCount = mpro->enumerator().keyCount();
		for (int i = 0; i < keyCount; i++)
		{
			const char* key = mpro->enumerator().key(i);
			qDebug() << " " << key;
		}
	}
}
