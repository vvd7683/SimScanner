#ifndef _PE32_H_
#define _PE32_H_

#include <Windows.h>

#define OFFSET_ERR		(~0)
#define RVA_ERR			(~0)

typedef DWORD __RVA32;

enum PE_TARGET {
	pet_Unknown = -1,
	pet_x86 = 0,
	pet_x64,
	pet_ARM,
	pet_x86_DLL,
	pet_x64_DLL,
	pet_ARM_DLL
};

enum PE_SYSTEM {
	pes_Unknown = -1,
	pes_Desktop = 0,
	pes_Mobile
};

union PIMAGE_NT {
	PVOID _is;
	PIMAGE_NT_HEADERS32 nt32;
	PIMAGE_NT_HEADERS64 nt64;
};

PIMAGE_NT_HEADERS32 getPE32(HANDLE hFileImage, ULONG FileImageSz = 0);
PVOID getModuleBase(HANDLE hFileImage,ULONG FileImageSz);

ULONG RVA2Offset32(HANDLE hFileImage,ULONG FileImageSz,__RVA32 RVA);

__RVA32 GetEntryPointRVA32(HANDLE hFileImage, ULONG FileImageSz);
DWORD GetEntryPointOffset32(HANDLE hFileImage, ULONG FileImageSz);
PBYTE GetEntryPoint32(HANDLE hFileImage, ULONG FileImageSz);

PIMAGE_SECTION_HEADER getPEsections32(PIMAGE_NT_HEADERS32 hPE);

#endif