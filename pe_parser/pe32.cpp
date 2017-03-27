#include "pe32.h"

PIMAGE_SECTION_HEADER getPEsections32(PIMAGE_NT_HEADERS32 hPE) {
	ULONG DirectoriesCount=hPE->OptionalHeader.NumberOfRvaAndSizes;
	char *ptr=(char *)hPE;
	ptr+=(ULONG)&((PIMAGE_NT_HEADERS32)NULL)->OptionalHeader+sizeof(IMAGE_OPTIONAL_HEADER32);
	return (PIMAGE_SECTION_HEADER)ptr;
}

PIMAGE_NT getPE(HANDLE hFileImage, PE_TARGET &pet, PE_SYSTEM &pes, LONG FileImageSz) {
	PIMAGE_NT pNT = { NULL };
	PIMAGE_DOS_HEADER pDOS = (PIMAGE_DOS_HEADER)hFileImage;
	if (pDOS->e_magic == IMAGE_DOS_SIGNATURE) {
		if ((!FileImageSz) || (pDOS->e_lfanew < FileImageSz)) {
			pNT.nt32 = (PIMAGE_NT_HEADERS32)((PBYTE)hFileImage + pDOS->e_lfanew);
			if (pNT.nt32->Signature == IMAGE_NT_SIGNATURE) {
				switch (pNT.nt32->FileHeader.Machine)
				{
				case IMAGE_FILE_MACHINE_I386:
					pet = pNT.nt32->FileHeader.Characteristics & IMAGE_FILE_DLL ? pet_x86_DLL : pet_x86;
					break;
				case IMAGE_FILE_MACHINE_AMD64:
					pet = pNT.nt64->FileHeader.Characteristics & IMAGE_FILE_DLL ? pet_x64_DLL : pet_x64;
					break;
					//case IMAGE_FILE_MACHINE_ARM:
				case IMAGE_FILE_MACHINE_ARMNT:
					pet = pNT.nt32->FileHeader.Characteristics & IMAGE_FILE_DLL ? pet_ARM_DLL : pet_ARM;
					break;
				default:
					pNT.nt32 = NULL;
					pet = pet_Unknown;
					pes = pes_Unknown;
					break;
				}

			}
		}
	}
	return pNT;
}

PIMAGE_NT_HEADERS32 getPE32(HANDLE hImage, ULONG ImageSz) {
	PE_TARGET pet;
	PE_SYSTEM pes;
	PIMAGE_NT pNT = getPE(hImage, pet, pes, ImageSz);
	if (pNT._is) {
		switch (pet)
		{
		case pet_x86:
		case pet_x86_DLL:
			return pNT.nt32;
		default:
			break;
		}
	}
	return NULL;
}

PVOID getModuleBase(HANDLE hFileImage,ULONG FileImageSz) {
	PVOID _result = NULL;
	if(PIMAGE_NT_HEADERS32 hPE = 
		getPE32(hFileImage, FileImageSz)) 
	{
		_result = (PVOID)hPE->OptionalHeader.ImageBase;
	}
	return _result;
}

ULONG RVA2Offset32(HANDLE hFileImage,ULONG FileImageSz,__RVA32 RVA)
{
	char *pFileImage=(char *)hFileImage;
	ULONG _result=OFFSET_ERR;
	PIMAGE_NT_HEADERS32 pPEheader=getPE32(hFileImage,FileImageSz);
	if(pPEheader)
	{
		ULONG i;
		ULONG SectionsCount=pPEheader->FileHeader.NumberOfSections;
		PIMAGE_SECTION_HEADER pSections = IMAGE_FIRST_SECTION(pPEheader);
		//PIMAGE_OPTIONAL_HEADER32 pOptionalHeader=&pPEheader->OptionalHeader;
		for(i=0;i<SectionsCount;i++)
		{
			ULONG SectionRVA=pSections[i].VirtualAddress;
			ULONG secSz=pSections[i].SizeOfRawData;
/*			if(!secSz)
				secSz=pSections[i].Misc.VirtualSize;*/
			ULONG SectionEndRVA=SectionRVA+secSz;
			if((RVA>=SectionRVA)&&(RVA<SectionEndRVA))
			{
				_result=RVA-SectionRVA+pSections[i].PointerToRawData;
				return _result;
			}
		}
		for(i=0;i<SectionsCount;i++)
		{
			ULONG SectionRVA=pSections[i].VirtualAddress;
			if(RVA>SectionRVA)
				return _result;
		}
		_result=RVA;
	}
	return _result;
}

__RVA32 GetEntryPointRVA32(HANDLE hFileImage, ULONG FileImageSz) {
	if(PIMAGE_NT_HEADERS32 hPE = getPE32(hFileImage, FileImageSz)) {
		return hPE->OptionalHeader.AddressOfEntryPoint;
	} else {
		return RVA_ERR;
	}
}

PBYTE GetEntryPoint32(HANDLE hFileImage, ULONG FileImageSz) {
	PIMAGE_NT_HEADERS32 hPE = getPE32(hFileImage, FileImageSz);
	ULONG Offset = RVA2Offset32(hFileImage, FileImageSz, 
		hPE->OptionalHeader.AddressOfEntryPoint);
	if(Offset != OFFSET_ERR) {
		PBYTE pImage = (PBYTE)hFileImage;
		return (pImage + Offset);
	}
	return NULL;
}

DWORD GetEntryPointOffset32(HANDLE hFileImage, ULONG FileImageSz) {
	PIMAGE_NT_HEADERS32 hPE = getPE32(hFileImage, FileImageSz);
	DWORD Offset = RVA2Offset32(hFileImage, FileImageSz, 
		hPE->OptionalHeader.AddressOfEntryPoint);
	return Offset;
}
