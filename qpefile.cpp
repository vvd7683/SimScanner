#include "qpefile.h"

QPeFile::QPeFile(QFileInfo &info) : QFile(info.absoluteFilePath()),
    parser(NULL), Info(info)
{
    init();
}

QPeFile::~QPeFile() {
    unmap(pHeader);
    close();
}

void QPeFile::init() {
    if(exists()) {
        //const int c_sz = size();
        if(open(QIODevice::Unbuffered |
                QIODevice::ReadOnly))
        {
            if(pHeader = map(0, 0x00010000)) {
                if(PIMAGE_NT_HEADERS32 pPE = getPE32(pHeader)) {
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
