#ifndef DL_EXPORT
#define DL_EXPORT

#ifdef MMIND_DL_SDK_EXPORTS
#define MMIND_DL_SDK_EXPORT __declspec(dllexport)
#else
#define MMIND_DL_SDK_EXPORT __declspec(dllimport)
#endif

#ifdef MMIND_SINGLE_SDK_EXPORTS
#define MMIND_SINGLE_SDK_EXPORT __declspec(dllexport)
#else
#define MMIND_SINGLE_SDK_EXPORT __declspec(dllimport)
#endif

#endif