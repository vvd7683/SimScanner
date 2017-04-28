#include "peParser.h"
//-----------------------------------------------------------------------------
peParser::peParser(HANDLE hFile, 
	ULONG FileSz) : hFileImage(hFile), 
	FileImageSz(FileSz),
	hPE(getPE32(hFile, FileSz))
{
	if (!hPE) {
		throw "There is no PE32 image";
	}
}

PIMAGE_SECTION_HEADER peParser::_get_sections() {
	return getPEsections32(hPE);
}

ULONG peParser::_get_sections_count() {
	return hPE->FileHeader.NumberOfSections;
}

double peParser::_get_section_entropy(ULONG index) {
	return Entropy(&pFileImage[Section[index].PointerToRawData],
		Section[index].SizeOfRawData).Value;
}
//-----------------------------------------------------------------------------
EntropyDiagram &peEntropyParser::_scan_entropy() {
    if(!entropy_diagram.size()) {
        const PBYTE c_start = pFileImage;
        const PBYTE c_end = c_start + FileImageSz;
        for (PBYTE Ptr = c_start;
            Ptr + _range < c_end;
            Ptr += _step)
        {
            //entropy_diagram.push_back(Entropy(Ptr, _range).Value);
        }
    }
    return entropy_diagram;
}

EntropyDiagram peEntropyParser::_scan_section_entropy(ULONG index) {
    EntropyDiagram sec_entropy_diagram;
	if (index < SectionsCount) {
		if (Section[index].SizeOfRawData && Section[index].PointerToRawData) {
			const PBYTE c_start = &pFileImage[Section[index].PointerToRawData];
			const PBYTE c_end = &c_start[Section[index].SizeOfRawData];
			for (PBYTE pSecPtr = c_start;
				pSecPtr + _range < c_end; 
				pSecPtr += _step) 
			{
                sec_entropy_diagram.push_back(Entropy(pSecPtr, _range).Value);
			}
		}
	}
    return sec_entropy_diagram;
}
//-----------------------------------------------------------------------------
