#ifndef VIP_H
#define VIP_H

#include <stdio.h>
#include <QString>
#include "vmetadump.h"

class _VIp
{
  // Q_GADGET

public:
  _VIp() {}
  _VIp(const _VIp& ip) { m_ip = ip.m_ip; }

  _VIp(const quint32& ip) { m_ip = ip; }
  operator quint32() { return m_ip; }

public:
  static QString toString(const _VIp& ip) { return QString::number(ip.m_ip);}
  static _VIp fromString(const QString& s) { return _VIp(s.toUInt()); }

  static void _initialize()
  {
    static bool initialized = false;
    if (!initialized)
    {
      bool res;
      res = QMetaType::registerConverter<_VIp, QString>(_VIp::toString);
      if (!res)
      {
        printf("QMetaType::registerConverter<_VIp, QString>(_VIp::ipToString) return false\n");
      }
      res = QMetaType::registerConverter<QString, _VIp>(_VIp::fromString);
      if (!res)
      {
        printf("QMetaType::registerConverter<QString, _VIp>(_VIp::stringToIp) return false\n");
      }
      initialized = true;
    }
  }
public:
  quint32 m_ip;
};
Q_DECLARE_METATYPE(_VIp)

#endif // VIP_H
