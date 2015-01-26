#ifndef VIP_H
#define VIP_H

#include <stdio.h>
#include <QString>
#include "vmetadump.h"

class VIp
{
  // Q_GADGET

public:
  VIp() {}
  VIp(const VIp& ip) { m_ip = ip.m_ip; }

  VIp(const quint32& ip) { m_ip = ip; }
  operator quint32() { return m_ip; }

public:
  static QString toString(const VIp& ip) { return QString::number(ip.m_ip);}
  static VIp fromString(const QString& s) { return VIp(s.toUInt()); }

  static void _initialize()
  {
    static bool initialized = false;
    if (!initialized)
    {
      bool res;
      res = QMetaType::registerConverter<VIp, QString>(VIp::toString);
      if (!res)
      {
        printf("QMetaType::registerConverter<VIp, QString>(VIp::ipToString) return false\n");
      }
      res = QMetaType::registerConverter<QString, VIp>(VIp::fromString);
      if (!res)
      {
        printf("QMetaType::registerConverter<QString, VIp>(VIp::stringToIp) return false\n");
      }
      initialized = true;
    }
  }
public:
  quint32 m_ip;
};
Q_DECLARE_METATYPE(VIp)

#endif // VIP_H
