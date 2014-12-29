#include "../common/vip.h"
#include "../common/vperson.h"
#include "../common/vvariant.h"

#include <QDebug>

int main()
{
	qDebug() << "sizeof(QVariant)" << sizeof(QVariant);
	qDebug() << "sizeof(VIp)" << sizeof(VIp);
	qDebug() << "sizeof(VPerson)" << sizeof(VPerson);
	return 0;
}
