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

const QString QPeFile::getSubsystemString() {
    switch(parser->cSubsystem)
    {
    case IMAGE_SUBSYSTEM_NATIVE:
        return tr("Native");
    case IMAGE_SUBSYSTEM_WINDOWS_GUI:
        return tr("GUI");
    case IMAGE_SUBSYSTEM_WINDOWS_CUI:
        return tr("Console");
    case IMAGE_SUBSYSTEM_OS2_CUI:
        return tr("OS/2 console");
    case IMAGE_SUBSYSTEM_POSIX_CUI:
        return tr("POSIX");
    case IMAGE_SUBSYSTEM_NATIVE_WINDOWS:
        return tr("Win9x driver");
    case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
        return tr("WinCE GUI");
    case IMAGE_SUBSYSTEM_EFI_APPLICATION:
        return tr("EFI");
    case IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
        return tr("EFI boot");
    case IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
        return tr("EFI driver");
    case IMAGE_SUBSYSTEM_EFI_ROM:
        return tr("EFI ROM");
    case IMAGE_SUBSYSTEM_XBOX:
        return tr("XBOX");
    case IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION:
        return tr("Windows boot");
    case IMAGE_SUBSYSTEM_UNKNOWN:
    default:
        return tr("unknown");
    }
}

EntropyDiagram &QPeFile::getEntropy() {
    return *parser->entropyDiagram;
}

EntropyDiagram &QPeFile::getEntropyDerivative() {
    return *parser->entropyDerivativeDiagram;
}

ExtremumDensityDiagram &QPeFile::getExtremumDensity() {
    return *parser->extremumDensity;
}

void QPeFile::init() {
    if(exists()) {
        //const int c_sz = size();
        if(open(QIODevice::Unbuffered |
                QIODevice::ReadOnly))
        {
            if(pHeader = map(0, size())) {
                if(parser = new peEntropyParser(pHeader, size())) {
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
