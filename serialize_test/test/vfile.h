#ifndef VFILE_H
#define VFILE_H

#include "vobject.h"

class VFile : public VObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    VFile(VObject* parent = 0);
    virtual ~VFile();

public:
    QString fileName() const;
    void setFileName(QString fileName);

signals:
    void fileNameChanged(QString fileName);

private:
    QString m_fileName;
};

#endif // VFILE_H
