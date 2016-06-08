/*
	N-Gaming Network | sa-core

	  Path:
		../utils/memory.cpp
	  Description:
		N/A
	  Licenses:
		N/A

	Copyright (c) 2016 N-Gaming Network (All rights reserved).
 */
#include "gracmd.h"

static bool memory_compare(const BYTE *data, const BYTE *pattern, const char *mask)
{
		for (; *mask; ++mask, ++data, ++pattern)
		{
				if (*mask == 'x' && *data != *pattern)
						return false;
		}
		return (*mask) == NULL;
}

DWORD Utils::Memory::FindPattern(char *pattern, char *mask) {
		DWORD i;
		DWORD size;
		DWORD address;
#ifdef _WIN32
		MODULEINFO info = { 0 };

		address = (DWORD)GetModuleHandle(NULL);
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(MODULEINFO));
		size = (DWORD)info.SizeOfImage;
#else
		address = 0x804b480; // around the elf base
		size = 0x8128B80 - address;
#endif
		for (i = 0; i < size; ++i)
		{
				if (memory_compare((BYTE *)(address + i), (BYTE *)pattern, mask))
						return (DWORD)(address + i);
		}
		return 0;
}

