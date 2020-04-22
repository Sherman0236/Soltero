#include "Utilities/Imports.hpp"

namespace Global
{
	struct
	{
		HMODULE Mono = NULL;
	} Modules;

	struct
	{
		typedef uint64_t(__fastcall* fnMonoImageLoaded) (char*);
		fnMonoImageLoaded MonoImageLoaded = nullptr;
	} Functions;
};