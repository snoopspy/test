#include <iostream>
#include <QCoreApplication>
#include "vtypeinfo.h"

class Obj
{
public:
	const char* className()
	{
		return VTypeInfo::className(typeid(*this));
	}
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	{
		const char* className = VTypeInfo::className(typeid(a));
		std::cout << className << std::endl;
		std::cout << a.metaObject()->className() << std::endl;
	}

	{
		Obj obj;
		const char* className = VTypeInfo::className(typeid(obj));
		std::cout << className << std::endl;
	}

	{
		Obj obj;
		const char* className = obj.className();
		std::cout << className << std::endl;
	}
}
