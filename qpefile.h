#ifndef QPEFILE_H
#define QPEFILE_H

#include <QFile>
#include <QString>
#include <QFileInfo>

#include "entropy_parser.h"

class QPeFile : public QFile
{
    Q_OBJECT
public:
    QPeFile(QFileInfo &info);
    ~QPeFile();
    const WORD getFlags() {return parser->cFlags;}
    const QString getFlagsString();
    const WORD getMachine() {return parser->cMachine;}
    const QString getMachineString();
    const QString getSubsystemString();
    const unsigned int getOptHeaderSz() {return parser->cOptHeaderSize;}
    const DWORD getImageBase() {return parser->cImageBase;}
    const DWORD getImageSize() {return parser->cImageSize;}
    const DWORD getEntry() {return parser->cEntry;}

    EntropyDiagram &getEntropy() {
        return *parser->entropyDiagram;
    }

private:
    void init();
    QFileInfo &Info;
    peEntropyParser *parser;
    PBYTE pHeader;
};

#endif // QPEFILE_H
