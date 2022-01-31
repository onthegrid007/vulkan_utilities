#ifndef VULKAN_COMMON_H
#define VULKAN_COMMON_H

#include "platformdetection.h"
#ifndef GLM_SETUP_INCLUDED
	#error "GLM must be included BEFORE including any files from VulkanUtilities!"
#endif

namespace VulkanUtilities { inline bool VulkanRuntimeDebug = true; }
#ifdef VULKAN_PLATFORM_WINDOWS
	#include <windows.h>
    #define VK_USE_PLATFORM_WIN32_KHR
	#define GLFW_EXPOSE_NATIVE_WIN32
	#define VK_API_VERSION VK_API_VERSION_1_2
	#define MAX_RENDER_OBJECTS 10000
	#include "vendor/volk/volk.h"
#endif

#define VULK_UTILITIES_STR "[VulkanUtilities]"
#define VULK_LOG_ERROR_STR "[ERROR]"
#define VKCALL_LOG_ERROR(call, res, file, line, funcsig) VULK_UTILITIES_STR + VULK_LOG_ERROR_STR + " In file: " + #file " : line " + #line + " :: " + #funcsig + " --> " + #call + " was unsucessful with error code: " + VkResultEnumToString(res)
#define VKCall(call) {\
	VkResult res = call;\
	if(res != VK_SUCCESS) {\
		VulkanRuntimeDebug ? cout << VKCALL_LOG_ERROR(#call, res, __FILE__, __LINE_, __FUNCSIG__) << endl : 0;\
		assert(call >= VK_SUCCESS);\
	}\
}

#include "VulkanBuffer.h"
#include "VulkanVertexPipeline.h"
#include "VulkanIndexPipeline.h"
#include "VulkanImage.h"
#endif