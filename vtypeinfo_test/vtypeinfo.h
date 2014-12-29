#ifndef VTYPEINFO_H
#define VTYPEINFO_H

#include <typeinfo>

class VTypeInfo
{
public:
	static const char* className(const std::type_info& ti);
};

#endif // VTYPEINFO_H
