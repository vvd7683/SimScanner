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
	ULONG _get_sections_count();
	double _get_section_entropy(ULONG index);
	__declspec(property(
		get = _get_sections))
		PIMAGE_SECTION_HEADER
		Section;
	__declspec(property(
		get = _get_sections_count))
		ULONG
		SectionsCount;
	__declspec(property(
		get = _get_section_entropy))
		double
		SectionEntropy[];
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
protected:
	union {
		HANDLE hFileImage;
		PBYTE pFileImage;
	};
	ULONG FileImageSz;
	PIMAGE_NT_HEADERS32 hPE;
};

class peEntropyParser : public peParser
{
public:
    typedef double EntropyPoint;//TODO: make pair
    typedef std::vector<EntropyPoint> EntropyDiagram;
	peEntropyParser(HANDLE hFile, 
		ULONG FileSz, 
		ULONG n_step = 1, 
		ULONG n_range = 0x200) : peParser(hFile, 
		FileSz),
		_step(n_step),
		_range(n_range)
	{}
    EntropyDiagram _scan_entropy();
    __declspec(property(
        get = _scan_entropy))
        EntropyDiagram
        entropyDiagram;
    EntropyDiagram _scan_section_entropy(ULONG index);
	__declspec(property(
		get = _scan_section_entropy))
		EntropyDiagram
		SectionEntropyDiagram[];
	//Getter/setter wraps internal variables for future development
	ULONG _get_step() { return _step; }
	ULONG _set_step(ULONG val) { return _step = val; }
	__declspec(property(
		get = _get_step,
		put = _set_step))
		ULONG Step;
	ULONG _get_range() { return _range; }
	ULONG _set_range(ULONG val) { return _range = val; }
	__declspec(property(
		get = _get_range, 
		put = _set_range))
		ULONG Range;
private:
	ULONG _step;
	ULONG _range;
};
#endif
