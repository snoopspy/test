#include <stdio.h>
#include "vmetadump.h"

void VMetaDump::dump(QVariant* var)
{
	int userType = var->userType();
	QVariant::Type type = var->type();
	const char* typeName = var->typeName();
	printf("userType=%d type=%d typeName=%s\n", userType, (int)type, typeName);
}

void VMetaDump::dump(QObject* obj, int ident)
{
	QString objectName = obj->objectName();
	dump((QMetaObject*)obj->metaObject(), obj, ident);
}

void VMetaDump::dump(QMetaObject* mobj, QObject* obj, int ident)
{
	const char* className = mobj->className();
	QString objectName = NULL;
	if (obj != NULL)
		objectName = obj->objectName();
	printf("%s%s %s\n", qPrintable(duplicate(' ', ident)), className, qPrintable(objectName));

	int propertyCount = mobj->propertyCount();
	for (int i = 0; i < propertyCount; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		dump(&mpro, obj, ident + 1);
	}
}

#include "vip.h"
void VMetaDump::dump(QMetaProperty *mpro, QObject* obj, int ident)
{
	const char* name = mpro->name();
	QVariant variant = obj->property(name);
	QString value = variant.toString();

	QString typeName = variant.typeName();
	if (mpro->isEnumType())
	{
		QMetaEnum menum = mpro->enumerator();
		typeName = menum.name();
		value = menum.key(variant.toInt());
	}

	printf("%s%s %s %s\n", qPrintable(duplicate(' ', ident)), qPrintable(typeName), name, qPrintable(value));
}

QString VMetaDump::duplicate(char ch, int count)
{
	QString res;
	for (int i = 0; i < count; i++)
		res += ch;
	return res;
}
