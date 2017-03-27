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
peEntropyParser::EntropyDiagram peEntropyParser::_scan_section_entropy(ULONG index) {
	std::vector<double> entropy_diagram;
	if (index < SectionsCount) {
		if (Section[index].SizeOfRawData && Section[index].PointerToRawData) {
			const PBYTE c_start = &pFileImage[Section[index].PointerToRawData];
			const PBYTE c_end = &c_start[Section[index].SizeOfRawData];
			for (PBYTE pSecPtr = c_start;
				pSecPtr + _range < c_end; 
				pSecPtr += _step) 
			{
				entropy_diagram.push_back(Entropy(pSecPtr, _range).Value);
			}
		}
	}
	return entropy_diagram;
}
//-----------------------------------------------------------------------------
