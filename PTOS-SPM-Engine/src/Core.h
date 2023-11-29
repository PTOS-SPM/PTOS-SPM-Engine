#pragma once

#ifdef PTOS_PLATFORM_WINDOWS
#ifdef PTOS_BUILD_DLL
#define PTOS_API __declspec(dllexport)
#else
#define PTOS_API __declspec(dllimport)
#endif
#else
#error Build not supported for this platform.
#endif