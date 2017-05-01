#ifndef _peParser_h_
#define _peParser_h_

#include <Windows.h>
#include <vector>
#include <exception>
#include "pe32.h"
#include "entropy.h"

class peParser
{
public:
	peParser(HANDLE hFile, ULONG FileSz);
	PIMAGE_SECTION_HEADER _get_sections();
    PIMAGE_DATA_DIRECTORY _get_directories();
    ULONG _get_directories_count();
	ULONG _get_sections_count();
    //double _get_section_entropy(ULONG index);
	__declspec(property(
		get = _get_sections))
		PIMAGE_SECTION_HEADER
		Section;
    __declspec(property(
        get = _get_directories))
        PIMAGE_DATA_DIRECTORY
        Directory;
    __declspec(property(
		get = _get_sections_count))
		ULONG
		SectionsCount;
    __declspec(property(
        get = _get_directories_count))
        ULONG
        DirectoriesCount;
    /*
	__declspec(property(
		get = _get_section_entropy))
		double
        SectionEntropy[];*/
    const WORD _get_machine() {
        return hPE->FileHeader.Machine;
    }
    __declspec(property(
                   get = _get_machine))
    const WORD cMachine;
    const WORD _get_flags() {
        return hPE->FileHeader.Characteristics;
    }
    __declspec(property(
                   get = _get_flags))
    const WORD cFlags;
    const unsigned int _get_opt_sz() {
        return hPE->FileHeader.SizeOfOptionalHeader;
    }
    __declspec(property(
                   get = _get_opt_sz))
    const unsigned int cOptHeaderSize;
    const DWORD _get_base() {
        return hPE->OptionalHeader.ImageBase;
    }
    __declspec(property(
                   get = _get_base))
    const DWORD cImageBase;
    const DWORD _get_size() {
        return hPE->OptionalHeader.SizeOfImage;
    }
    __declspec(property(
                   get = _get_size))
    const DWORD cImageSize;
    const DWORD _get_entry() {
        return hPE->OptionalHeader.AddressOfEntryPoint;
    }
    __declspec(property(
                   get = _get_entry))
    const DWORD cEntry;
    const WORD _get_subsystem() {
        return hPE->OptionalHeader.Subsystem;
    }
    __declspec(property(
                   get = _get_subsystem))
    const WORD cSubsystem;
    const DWORD getMemAlign() {
        return hPE->OptionalHeader.SectionAlignment;
    }
    __declspec(property(
                   get = getMemAlign))
    const DWORD cMemAlign;
protected:
	union {
		HANDLE hFileImage;
		PBYTE pFileImage;
	};
	ULONG FileImageSz;
	PIMAGE_NT_HEADERS32 hPE;
};

#endif
