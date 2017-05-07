#ifndef QPEFILE_H
#define QPEFILE_H

#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QMap>

#include "entropy_parser.h"

typedef struct SSSection {
    QString SectionName;
    PIMAGE_SECTION_HEADER pSection;
    PBYTE ptr;
    EntropyType entropy_val;
    EntropyDiagram sec_entropy;
    SSSection(PBYTE pImage = NULL,
              ULONG ImageSz = 0,
              PIMAGE_SECTION_HEADER pSec = NULL);
} *PSSSection;

typedef struct SSDirectory {
    SSDirectory(PIMAGE_DATA_DIRECTORY dirs = NULL,
                const int c_idx = 0) : index(c_idx),
        Directory(dirs + c_idx)
    {
        //
    }
    void set_dir(PIMAGE_DATA_DIRECTORY dirs,
                 const int c_idx)
    {
        Directory = dirs + c_idx;
    }

    QString DirectoryName() {
        switch(index)
        {
        case IMAGE_DIRECTORY_ENTRY_EXPORT:
            return QString("Export Table");
        case IMAGE_DIRECTORY_ENTRY_IMPORT:
            return QString("Import Table");
        case IMAGE_DIRECTORY_ENTRY_RESOURCE:
            return QString("Resource Directory");
        case IMAGE_DIRECTORY_ENTRY_EXCEPTION:
            return QString("Exception Directory");
        case IMAGE_DIRECTORY_ENTRY_SECURITY:
            return QString("Security Directory");
        case IMAGE_DIRECTORY_ENTRY_BASERELOC:
            return QString("Base Relocation Table");
        case IMAGE_DIRECTORY_ENTRY_DEBUG:
            return QString("Debug Directory");
        case IMAGE_DIRECTORY_ENTRY_ARCHITECTURE:
            return QString("Architecture Specific Data");
        case IMAGE_DIRECTORY_ENTRY_GLOBALPTR:
            return QString("RVA of GP");
        case IMAGE_DIRECTORY_ENTRY_TLS:
            return QString("TLS Directory");
        case IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG:
            return QString("Load Configuration Directory");
        case IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT:
            return QString("Bound Import Directory");
        case IMAGE_DIRECTORY_ENTRY_IAT:
            return QString("Import Address Table");
        case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
            return QString("Delay Load Import Descriptors");
        case IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR:
            return QString("COM Runtime descriptor");
        default:
            return QString("<Unknown>");
        }
    }
    QString DirectoryComment() {
        switch(index)
        {
        case IMAGE_DIRECTORY_ENTRY_EXPORT:
            return QString("Export Table");
        case IMAGE_DIRECTORY_ENTRY_IMPORT:
            return QString("Import Table");
        case IMAGE_DIRECTORY_ENTRY_RESOURCE:
            return QString("Resource Directory");
        case IMAGE_DIRECTORY_ENTRY_EXCEPTION:
            return QString("Exception Directory");
        case IMAGE_DIRECTORY_ENTRY_SECURITY:
            return QString("Signed binary");
        case IMAGE_DIRECTORY_ENTRY_BASERELOC:
            return QString("Fixups");
        case IMAGE_DIRECTORY_ENTRY_DEBUG:
            return QString("Debug information");
        case IMAGE_DIRECTORY_ENTRY_ARCHITECTURE:
            return QString("Architecture Specific Data");
        case IMAGE_DIRECTORY_ENTRY_GLOBALPTR:
            return QString("Unused");
        case IMAGE_DIRECTORY_ENTRY_TLS:
            return QString("Thread Local Storage");
        case IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG:
            return QString("Load Configuration Directory");
        case IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT:
            return QString("Bound Import Directory");
        case IMAGE_DIRECTORY_ENTRY_IAT:
            return QString("Import Address Table");
        case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT:
            return QString("Lazy binding");
        case IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR:
            return QString(".NET binary");
        default:
            return QString("RESERVED");
        }
    }
    int index;
    PIMAGE_DATA_DIRECTORY Directory;
} *PSSDirectory;

typedef QVector<SSSection *> SectionMap;
typedef QVector<SSDirectory> DirectoryMap;

class QPeFile : public QFile
{
    Q_OBJECT
public:
    QPeFile(QFileInfo &info);
    ~QPeFile();
    const WORD getFlags();
    const QString getFlagsString();
    const WORD getMachine();
    const QString getMachineString();
    const QString getSubsystemString();
    const unsigned int getOptHeaderSz();
    const DWORD getImageBase();
    const DWORD getImageSize();
    const DWORD getEntry();
    const DWORD memAlign(DWORD val);

    EntropyDiagram &getEntropy();
    SectionMap &getSections();
    DirectoryMap &getDirectories();
private:
    void init();
    void deinit();
    QFileInfo &Info;
    peEntropyParser *parser;
    PBYTE pHeader;
    SectionMap sec_map;
    DirectoryMap dir_map;
};

#endif // QPEFILE_H
