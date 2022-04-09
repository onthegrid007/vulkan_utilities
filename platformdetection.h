#ifdef _WIN32
	#ifdef _WIN64
		#define VULKAN_PLATFORM_WINDOWS
	#else
		#error "x86/32 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#error "Android is not supported!"
#elif defined(__linux__)
	#error "Linux is not supported!"
#else
	#define VULKAN_PLATFORM_UNDEFINED
	#error "Unknown platform!"
#endif

#ifndef GLM_SETUP_INCLUDED
	#error "GLM must be included BEFORE including any files from VulkanUtilities!"
#endif