#pragma once

#define PLATFORM_WINDOWS

#ifdef PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define ENGINE_API declspec(dllexport)
	#else
		#define ENGINE_API declspec(dllimport)
	#endif

#else 
	#error Windows platform needed to build this Engine
#endif