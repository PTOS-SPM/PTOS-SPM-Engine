#pragma once

#ifdef PTOS_PLATFORM_WINDOWS
#if defined PTOS_BUILD_STATIC
#define PTOS_API 
#elif defined PTOS_BUILD_DLL
#define PTOS_API __declspec(dllexport)
#else
#define PTOS_API __declspec(dllimport)
#endif
#else
#error Build not supported for this platform.
#endif

#ifdef PTOS_ASSERTS
#define PTOS_CORE_ASSERT(x, ...) { if(!(x)) { PTOS_CORE_ERR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define PTOS_ASSERT(x, ...) { if(!(x)) { PTOS_ERR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
#define PTOS_CORE_ASSERT(x, ...)
#define PTOS_ASSERT(x, ...)
#endif

//TODO add build flags for renderer inclusion
