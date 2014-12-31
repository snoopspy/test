#ifndef VLOG_H
#define VLOG_H

#include <QObject>

class VLog : public QObject
{
	Q_OBJECT

public:
	enum VShowDateTime
	{
		None,
		Time,
		DateTime
	};

public:
	explicit VLog(QObject *parent = 0);

signals:

public slots:

private:
	VShowDateTime m_showDateTime;
};

#endif // VLOG_H
