#ifndef VMAC_H
#define VMAC_H

#include <stdio.h>
#include <QString>
#include <QMetaType>

class _VMac
{
  static const int MAC_SIZE = 6;

public:
  _VMac() {}
  _VMac(const _VMac& rhs) { memcpy(this->mac, rhs.mac, MAC_SIZE); }

  _VMac(const QString& mac) { memcpy(this->mac, qPrintable(mac), MAC_SIZE); }
  operator QString() const { return QString((const char*)mac); }

  bool operator == (const _VMac& rhs) { return memcmp(this->mac, rhs.mac, MAC_SIZE) == 0; }
  bool operator != (const _VMac& rhs) { return memcmp(this->mac, rhs.mac, MAC_SIZE) != 0; }

  static QString toString(const _VMac& mac) { return QString(mac); }
  static _VMac fromString(const QString& s) { return _VMac(s); }

  static void _initialize()
  {
    static bool initialized = false;
    if (!initialized)
    {
      bool res;
      res = QMetaType::registerConverter<_VMac, QString>(_VMac::toString);
      if (!res)
      {
        printf("QMetaType::registerConverter<_VMac, QString>(_VMac_::ipToString) return false\n");
      }
      res = QMetaType::registerConverter<QString, _VMac>(_VMac::fromString);
      if (!res)
      {
        printf("QMetaType::registerConverter<QString, _VMac>(_VMac::stringToIp) return false\n");
      }
      initialized = true;
    }
  }

private:
  unsigned char mac[MAC_SIZE];
};
Q_DECLARE_METATYPE(_VMac)

#endif // VMAC_H
