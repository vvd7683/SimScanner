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
