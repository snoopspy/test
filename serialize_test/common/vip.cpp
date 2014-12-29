#include "vip.h"

VIp::VIp()
{
    m_ip = 0;
}

VIp::VIp(unsigned int ip)
{
    m_ip = ip;
}

VIp::VIp(const VIp& rhs)
{
    m_ip = rhs.m_ip;
}

VIp::~VIp()
{

}

