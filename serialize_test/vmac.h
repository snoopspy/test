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

	static void registerConverter()
	{
		static bool registered = false;
		if (!registered)
		{
			bool res;
			res = QMetaType::registerConverter<VMac, QString>(VMac::toString);
			if (!res)
			{
				printf("QMetaType::registerConverter<VIp, QString>(VIp::ipToString) return false\n");
			}
			res = QMetaType::registerConverter<QString, VMac>(VMac::fromString);
			if (!res)
			{
				printf("QMetaType::registerConverter<QString, VIp>(VIp::stringToIp) return false\n");
			}
			/*
			VIp ip1(1234);
			QVariant variant = QVariant::fromValue<VIp>(ip1);
			VIp ip2 = qvariant_cast<VIp>(variant);
			*/
			registered = true;
		}
	}

private:
	unsigned char mac[MAC_SIZE];
};
Q_DECLARE_METATYPE(VMac)

#endif // VMAC_H
