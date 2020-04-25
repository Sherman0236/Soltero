#include "Utilities/Imports.hpp"
#include "Structure.hpp"

void Main()
{
	Global::Modules.Mono = GetModuleHandleA("mono-2.0-bdwgc.dll");																						// Get a handle to the mono module
	if (!Global::Modules.Mono)
	{
		printf("Mono module not loaded!\n");
		return;
	}

	Global::Functions.MonoImageLoaded = reinterpret_cast<uint64_t(__fastcall *)(char*)>(GetProcAddress(Global::Modules.Mono, "mono_image_loaded"));		// Get the address of the function 'mono_image_loaded'
	if (!Global::Functions.MonoImageLoaded)
	{
		printf("Mono_Image_Loaded not found!\n");
		return;
	}

	printf("Address\tSize\tName\n");
	uint64_t pImage = Global::Functions.MonoImageLoaded((char*)"Assembly-CSharp");																		// Call the function for Assembly-CSharp and store the return
	printf("%I64X\t%I32X\t%s\n", pImage, *reinterpret_cast<uint32_t*>(pImage + 0x18), pImage);															
	*reinterpret_cast<uint32_t*>(pImage + 0x18) = 0x7BF298;																								// Write the correct image length
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Main), nullptr, 0, nullptr);													// Create a thread for ourself
	}

	return TRUE;
}