#ifndef PERSON_H
#define PERSON_H

#include <QMetaType>
#include <QObject>

class VPerson : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int age READ age WRITE setAge)
public:
	VPerson();
	VPerson(int age);
	VPerson(const VPerson& rhs);
	virtual ~VPerson();

	int age() const;
	void setAge(int age);
private:
	int m_age;
};
Q_DECLARE_METATYPE(VPerson)

#endif // PERSON_H
