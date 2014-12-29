#include <QCoreApplication>
#include <QDebug>

#include "obj1.h"
#include "obj2.h"
#include "vvariant.h"

void test(Obj& obj)
{
	QVariant variant;
	VVariantUtil::dump(variant);
	variant = obj;
	VVariantUtil::dump(variant);
}

int main(int argc, char *argv[])
{
	Q_UNUSED(argc)
	Q_UNUSED(argv)

	qDebug() << "sizeof(QVariant)" << sizeof(QVariant);
	qDebug() << "sizeof(Obj)" << sizeof(Obj);
	qDebug() << "sizeof(Obj1)" << sizeof(Obj1);
	qDebug() << "sizeof(Obj2)" << sizeof(Obj2);
	qDebug() << "";

	{
		Obj obj;
		QVariant variant;

		VVariantUtil::dump(variant);
		variant = obj;
		VVariantUtil::dump(variant);
	}

	{
		Obj1 obj1(1);
		QVariant variant;

		VVariantUtil::dump(variant);
		variant = obj1;
		VVariantUtil::dump(variant);
	}

	{
		Obj2 obj2(2);
		QVariant variant;

		VVariantUtil::dump(variant);
		variant = obj2;
		VVariantUtil::dump(variant);
	}

	/*
	{
		void* p;
		int type = QMetaType::type("Obj2");
		p = QMetaType::create(type);
		QVariant variant;
		variant.setValue<Obj2>(p);
		VVariantUtil::dump(variant);
	}
	*/

	return 0;
}
