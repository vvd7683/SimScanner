#ifndef QPEFILE_H
#define QPEFILE_H

#include <QFile>
#include <QString>
#include <QFileInfo>

#include "pe_parser/peParser.h"

class QPeFile : public QFile
{
    Q_OBJECT
public:
    QPeFile(QFileInfo &info);
    ~QPeFile();
    const WORD getFlags() {return parser->cFlags;}
private:
    void init();
    QFileInfo &Info;
    peParser *parser;
    PBYTE pHeader;
};

#endif // QPEFILE_H
