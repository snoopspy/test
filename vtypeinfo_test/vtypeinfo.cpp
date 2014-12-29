#include <cxxabi.h>
#include "vtypeinfo.h"

const char* VTypeInfo::className(const std::type_info& ti)
{
	int status;
	const char* res = ti.name();
	res = abi::__cxa_demangle(res, 0, 0, &status);
	return res;
}
