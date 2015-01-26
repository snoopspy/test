#ifndef VMAC_H
#define VMAC_H

#include <stdio.h>
#include <QString>
#include <QMetaType>

class VMac
{
  static const int MAC_SIZE = 6;

public:
  VMac() {}
  VMac(const VMac& rhs) { memcpy(this->mac, rhs.mac, MAC_SIZE); }

  VMac(const QString& mac) { memcpy(this->mac, qPrintable(mac), MAC_SIZE); }
  operator QString() const { return QString((const char*)mac); }

  bool operator == (const VMac& rhs) { return memcmp(this->mac, rhs.mac, MAC_SIZE) == 0; }
  bool operator != (const VMac& rhs) { return memcmp(this->mac, rhs.mac, MAC_SIZE) != 0; }

  static QString toString(const VMac& mac) { return QString(mac); }
  static VMac fromString(const QString& s) { return VMac(s); }

  static void _initialize()
  {
    static bool initialized = false;
    if (!initialized)
    {
      bool res;
      res = QMetaType::registerConverter<VMac, QString>(VMac::toString);
      if (!res)
      {
        printf("QMetaType::registerConverter<_VMac, QString>(_VMac_::ipToString) return false\n");
      }
      res = QMetaType::registerConverter<QString, VMac>(VMac::fromString);
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
Q_DECLARE_METATYPE(VMac)

#endif // VMAC_H
