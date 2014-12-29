#ifndef VIP_H
#define VIP_H

#include <QMetaType>

class VIp
{
public:
	VIp();
	VIp(unsigned int ip);
	VIp(const VIp& rhs);
	~VIp();

	void foo(unsigned int& rhs) { Q_UNUSED(rhs) }
//private:
public: // gilgil temp
	unsigned int m_ip;
};
Q_DECLARE_METATYPE(VIp)

#endif // VIP_H
