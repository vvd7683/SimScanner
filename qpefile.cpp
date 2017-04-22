#include "qpefile.h"

QPeFile::QPeFile(QFileInfo &info) : QFile(info.absoluteFilePath()),
    parser(NULL), Info(info)
{
    init();
}

QPeFile::~QPeFile() {
    delete parser;
    unmap(pHeader);
    close();
}

const QString QPeFile::getFlagsString() {
    QString result = QString();
    if(parser->cFlags & IMAGE_FILE_DLL)
        result.append("dynamic library; ");
    if(parser->cFlags & IMAGE_FILE_RELOCS_STRIPPED)
        result.append("no relocations; ");
    return result;
}

const QString QPeFile::getMachineString() {
    switch(parser->cMachine)
    {
    case IMAGE_FILE_MACHINE_I386:
        return tr("Intel 386");
    case 0x160:
        return tr("MIPS big-endian");
    case IMAGE_FILE_MACHINE_R3000:
    case IMAGE_FILE_MACHINE_R4000:
    case IMAGE_FILE_MACHINE_R10000:
        return tr("MIPS little-endian");
    case IMAGE_FILE_MACHINE_WCEMIPSV2:
        return tr("MIPS little-endian WCE v2");
    case IMAGE_FILE_MACHINE_ALPHA:
        return tr("Alpha AXP");
    case 0:
    default:
        return tr("UNKNOWN");
    }
}

void QPeFile::init() {
    if(exists()) {
        //const int c_sz = size();
        if(open(QIODevice::Unbuffered |
                QIODevice::ReadOnly))
        {
            if(pHeader = map(0, size())) {
                if(parser = new peParser(pHeader, size())) {
                    //
                } else {
                    unmap(pHeader);
                    close();
                    throw;
                }
            } else {
                close();
                throw;
            }
        }
    } else {
        throw;
    }
}
