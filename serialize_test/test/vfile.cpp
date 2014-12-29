#include "vfile.h"

VFile::VFile(VObject* parent) : VObject(parent)
{
    m_fileName = "";
}

VFile::~VFile()
{

}

QString VFile::fileName() const
{
    return m_fileName;
}

void VFile::setFileName(QString fileName)
{
    m_fileName = fileName;
}
