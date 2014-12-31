#ifndef VLOG_H
#define VLOG_H

#include <QObject>
#include "vvariant.h"

class VLog : public QObject
{
	Q_OBJECT
	Q_ENUMS(VShowDateTime)
	Q_PROPERTY(VShowDateTime showDateTime READ showDateTime WRITE setShowDateTime)
public:
	enum VShowDateTime
	{
		None,
		Time,
		DateTime
	};

public:
	explicit VLog(QObject *parent = 0);

	V_PROPERTY_FUNC(VShowDateTime, showDateTime, setShowDateTime, m_showDateTime)

private:
	VShowDateTime m_showDateTime;
};
Q_DECLARE_METATYPE(VLog::VShowDateTime)

#endif // VLOG_H
