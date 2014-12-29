#include <iostream>
#include <QCoreApplication>
#include "vtypeinfo.h"

class ns {
public:
	class Obj
	{
	public:
		virtual ~Obj() {}
		const char* className()
		{
			return VTypeInfo::className(typeid(*this));
		}
	};

	class Obj2 : public Obj
	{

	};
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
		ns::Obj obj;
		const char* className = VTypeInfo::className(typeid(obj));
		std::cout << className << std::endl;
	}

	{
		ns::Obj obj;
		const char* className = obj.className();
		std::cout << className << std::endl;
	}

	{
		ns::Obj* obj = new ns::Obj2;
		const char* className = obj->className();
		std::cout << className << std::endl;
	}
}
