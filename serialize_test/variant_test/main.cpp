#include "../common/vip.h"
#include "../common/vperson.h"
#include "../common/vvariant.h"

#include <QVariant>

#include <QDebug>

int main()
{
	{
		QVariant v;
		VVariant::dump(v);
	}

	{
		QVariant v;
		int i = 1;
		v.setValue(i);
		VVariant::dump(v);
	}

	{
		QVariant v;
		char ch = 'A';
		v.setValue(ch);
		VVariant::dump(v);
	}

	{
		QVariant v;
		VIp ip(34);
		v.setValue(ip);
		VVariant::dump(v);
	}

	{
		QVariant v;
		VPerson person(40);
		v.setValue(person);
		VVariant::dump(v);
	}

	return 0;
}
