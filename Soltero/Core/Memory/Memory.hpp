#pragma once
#include <Psapi.h>

namespace Memory
{
	template<typename T>
	bool ValidatePointer(T lpAddress)
	{
		if (lpAddress == 0)
			return false;

		MEMORY_BASIC_INFORMATION mbi;
		SIZE_T size = VirtualQuery(reinterpret_cast<LPVOID>(lpAddress), &mbi, sizeof(MEMORY_BASIC_INFORMATION));

		if (size == 0)
			return false;

		if ((BYTE*)(lpAddress + sizeof(T)) < mbi.BaseAddress || (BYTE*)(lpAddress + sizeof(T)) > ((BYTE*)mbi.BaseAddress + mbi.RegionSize))
			return false;

		return !(mbi.Protect & PAGE_GUARD) && mbi.Protect != PAGE_NOACCESS && mbi.State == MEM_COMMIT &&
			mbi.Protect & (PAGE_READONLY | PAGE_EXECUTE_READ | PAGE_READWRITE | PAGE_EXECUTE_READWRITE);
	}
};