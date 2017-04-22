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
	typedef std::vector<double> EntropyDiagram;
	peEntropyParser(HANDLE hFile, 
		ULONG FileSz, 
		ULONG n_step = 1, 
		ULONG n_range = 0x200) : peParser(hFile, 
		FileSz),
		_step(n_step),
		_range(n_range)
	{}
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
