#ifndef VULKANUTILITIES_H_
#define VULKANUTILITIES_H_

#include "common.h"
#include <set>

namespace VulkanUtilities {

	struct QueueFamilyIndices {
		optional<uint32_t> graphicsFamily;
		optional<uint32_t> presentFamily;

		inline bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		vector<VkSurfaceFormatKHR> formats;
		vector<VkPresentModeKHR> presentModes;
	};

	inline string VkResultEnumToString(VkResult& result) {
		switch(result) {
			case VK_SUCCESS: return "VK_SUCCESS";
			case VK_NOT_READY: return "VK_NOT_READY";
			case VK_TIMEOUT: return "VK_TIMEOUT";
			case VK_EVENT_SET: return "VK_EVENT_SET";
			case VK_EVENT_RESET: return "VK_EVENT_RESET";
			case VK_INCOMPLETE: return "VK_INCOMPLETE";
			case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
			case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
			case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
			case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
			case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
			case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
			case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
			case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
			case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
			case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
			case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL";
			case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN";
			case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY";
			case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
			case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION";
			case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
			case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
			case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
			case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
			case VK_ERROR_INCOMPATIBLE_VERSION_KHR: return "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
			case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
			case VK_ERROR_NOT_PERMITTED_EXT: return "VK_ERROR_NOT_PERMITTED_EXT";
			case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
			case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR";
			case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR";
			case VK_OPERATION_DEFERRED_KHR: return "VK_OPERATION_DEFERRED_KHR";
			case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR";
			case VK_PIPELINE_COMPILE_REQUIRED_EXT: return "VK_PIPELINE_COMPILE_REQUIRED_EXT";
			case VK_RESULT_MAX_ENUM: return "VK_RESULT_MAX_ENUM";
			default: return "Unknown VkResult Enum!";
		}
	}

	inline string VkPhysicalDeviceTypeEnumToString(VkPhysicalDeviceType pdt) {
		switch(pdt) {
			case VK_PHYSICAL_DEVICE_TYPE_OTHER: return "VK_PHYSICAL_DEVICE_TYPE_OTHER";
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";
			case VK_PHYSICAL_DEVICE_TYPE_CPU: return "VK_PHYSICAL_DEVICE_TYPE_CPU";
			case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM: return "VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM";
			default: return "Unknown VkPhysicalDeviceType Enum!";
		};
	}

	inline void printPDProps(VkPhysicalDeviceProperties& props) {
		cout << "Device Name: " << props.deviceName << endl;
		cout << "Driver Version: " << props.driverVersion << endl;
		cout << "Device Type: " << VkPhysicalDeviceTypeEnumToString(props.deviceType) << endl;
	}

	inline QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR& surface) {
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, 0);

		vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}

	inline bool checkDeviceExtensionSupport(VkPhysicalDevice& pd, vector<const char*>& deviceExtensions) {
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(pd, 0, &extensionCount, 0);
		vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(pd, 0, &extensionCount, availableExtensions.data());

		set<string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions)
			requiredExtensions.erase(extension.extensionName);

		return requiredExtensions.empty();
	}

	inline SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& pd, VkSurfaceKHR& surface) {
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pd, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(pd, surface, &formatCount, 0);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(pd, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(pd, surface, &presentModeCount, 0);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(pd, surface, &presentModeCount, details.presentModes.data());
		}
		return details;
	}

	inline bool isDeviceSuitable(VkPhysicalDevice& pd, vector<const char*>& deviceExtensions, VkSurfaceKHR& surface) {
		QueueFamilyIndices indices = findQueueFamilies(pd, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(pd, deviceExtensions);

		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(pd, surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(pd, &supportedFeatures);

		return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
	}

	inline void printPhysicalDevices(vector<VkPhysicalDevice>& devices) {
		for(uint32_t i = 0; i < devices.size(); i++) {
			VkPhysicalDeviceProperties props;
			vkGetPhysicalDeviceProperties(devices[i], &props);
			cout << "Physical Device: " << i << endl;
			printPDProps(props);
			cout << endl;
		}
	}

	inline bool selectPDwDT(VkPhysicalDevice& pd, VkPhysicalDeviceType&& dt, vector<const char*>& deviceExtensions, VkSurfaceKHR& surface) {
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(dt, &props);	
		return (props.deviceType == dt && isDeviceSuitable(pd, deviceExtensions, surface));
	}

	inline VkPhysicalDevice pickPhysicalDevice(vector<VkPhysicalDevice>& devices, vector<const char*>& deviceExtensions, VkSurfaceKHR& surface) {
		if(VulkanRuntimeDebug) printPhysicalDevices(devices);
		for(uint32_t i = 0; i < devices.size(); i++) {
			if(selectPDwDT(devices[i], VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU, deviceExtensions, surface)) {
				if(VulkanRuntimeDebug) cout << "Picking Discrete GPU ID: " << i << endl << endl;
				return devices[i];
			}
		}
		for(uint32_t i = 0; i < devices.size(); i++) {
			if(selectPDwDT(devices[i], VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU, deviceExtensions, surface)) {
				if(VulkanRuntimeDebug) cout << "Picking Integrated GPU ID: " << i << endl << endl;
				return devices[i];
			}
		}
		for(uint32_t i = 0; i < devices.size(); i++) {
			if(selectPDwDT(devices[i], VK_PHYSICAL_DEVICE_TYPE_OTHER, deviceExtensions, surface)) {
				if(VulkanRuntimeDebug) cout << "Picking Other Device ID: " << i << endl << endl;
				return devices[i];
			}
		}
		if(devices.size() > 0) {
			if(VulkanRuntimeDebug) cout << "No suitable device found! Picking fallback device: " << devices.size() - 1 << endl;
			return devices[devices.size() - 1];
		}
		throw "No physical devices avaliable!";
		return VK_NULL_HANDLE;
	}

	inline VkInstance createInstance() {
		assert(volkGetInstanceVersion() >= VK_API_VERSION);
		VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
		VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
		appInfo.apiVersion = VK_API_VERSION;
		createInfo.pApplicationInfo = &appInfo;
	//	uint32_t extensionCount;
	//	VKCall(vkEnumerateInstanceExtensionProperties(0, &extensionCount, 0));
	//	vector<VkExtensionProperties> extensionProperties(extensionCount);
	//	VKCall(vkEnumerateInstanceExtensionProperties(0, &extensionCount, extensionProperties.data()));
		vector<const char*> extensionLayers;
	//	for(auto& property : extensionProperties)
	//		LOG(property.extensionName);
	//		extensionLayers.emplace_back(property.extensionName);
	#if VULKAN_PLATFORM_WINDOWS
		extensionLayers.emplace_back("VK_KHR_surface");
		extensionLayers.emplace_back("VK_KHR_win32_surface");
	#endif

	createInfo.ppEnabledExtensionNames = extensionLayers.data();
	createInfo.enabledExtensionCount = extensionLayers.size();

	if(VulkanRuntimeDebug) {
		vector<const char*> debugLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		createInfo.ppEnabledLayerNames = debugLayers.data();
		createInfo.enabledLayerCount = debugLayers.size();
	}

		VkInstance vkInstance;
		VKCall(vkCreateInstance(&createInfo, 0, &vkInstance));
		assert(vkInstance);
		volkLoadInstance(vkInstance);
		return vkInstance;
	}

	inline VkPhysicalDevice getPhysicalDevice(VkInstance& instance, vector<const char*>& deviceExtensions, VkSurfaceKHR& surface) {
		uint32_t pdCount;
		VKCall(vkEnumeratePhysicalDevices(instance, &pdCount, 0));
		vector<VkPhysicalDevice> physicalDevices(pdCount);
		VKCall(vkEnumeratePhysicalDevices(instance, &pdCount, physicalDevices.data()));
		VkPhysicalDevice pd = pickPhysicalDevice(physicalDevices, deviceExtensions, surface);
		assert(pd);
		return pd;
	}

	inline uint32_t getGraphicsQueueFamily(VkPhysicalDevice& pd) {
		uint32_t propertiesCount;
		vkGetPhysicalDeviceQueueFamilyProperties(pd, &propertiesCount, 0);
		vector<VkQueueFamilyProperties> properties(propertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(pd, &propertiesCount, properties.data());
		for(uint32_t i = 0; i < properties.size(); i++)
			if(properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				return i;
		assert(!"Physical Device does not support graphics, is this a compute only device?");
		return VK_QUEUE_FAMILY_IGNORED;
	}

	inline VkDevice createDevice(VkPhysicalDevice& pd, vector<const char*>& extensions, uint32_t familyIndex) {
		VkDeviceQueueCreateInfo createQueueInfo = { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
		VkDeviceCreateInfo createInfo = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };

		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledExtensionCount = extensions.size();

		VkPhysicalDeviceFeatures supportedFeatures = {};
		vkGetPhysicalDeviceFeatures(pd, &supportedFeatures);

		VkPhysicalDeviceMeshShaderFeaturesNV featuresMesh = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV };
		featuresMesh.taskShader = true;
		featuresMesh.meshShader = true;

		VkPhysicalDeviceVulkan12Features features12 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
	//	features12.drawIndirectCount = true;
		features12.storageBuffer8BitAccess = true;
		features12.uniformAndStorageBuffer8BitAccess = true;
	//	features12.storagePushConstant8 = true;
	//	features12.shaderFloat16 = true;
	//	features12.shaderInt8 = true;
		features12.samplerFilterMinmax = true;
		features12.scalarBlockLayout = true;

		features12.samplerMirrorClampToEdge = true;
		features12.descriptorIndexing = true;
		features12.shaderOutputViewportIndex = true;
		features12.shaderOutputLayer = true;

		features12.pNext = &featuresMesh;

		VkPhysicalDeviceFeatures2 features = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
		features.features.multiDrawIndirect = supportedFeatures.multiDrawIndirect;
		features.features.pipelineStatisticsQuery = supportedFeatures.pipelineStatisticsQuery;
		features.features.shaderInt16 = supportedFeatures.shaderInt16;
		features.features.shaderInt64 = supportedFeatures.shaderInt64;
		features.features.shaderFloat64 = supportedFeatures.shaderFloat64;
		features.features.samplerAnisotropy = supportedFeatures.samplerAnisotropy;
		features.pNext = &features12;

		createInfo.pNext = &features;

		float queuePriorities[] = { 1.0 };

		createQueueInfo.queueFamilyIndex = familyIndex;
		createQueueInfo.queueCount = 1;
		createQueueInfo.pQueuePriorities = queuePriorities;

		createInfo.queueCreateInfoCount = 1;
		createInfo.pQueueCreateInfos = &createQueueInfo;
		VkDevice device;
		VKCall(vkCreateDevice(pd, &createInfo, 0, &device));
		assert(device);
		volkLoadDevice(device);
		return device;
	}

	inline VkSurfaceKHR createSurface(VkInstance& instance, Window& window) {
	#ifdef VK_USE_PLATFORM_WIN32_KHR
		VkWin32SurfaceCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
		auto& hinstance = window.GetHInstance();
		hinstance = GetModuleHandle(0);
		createInfo.hinstance = hinstance;
		createInfo.hwnd = glfwGetWin32Window(window.GetGLFWWindow());
		VkSurfaceKHR surface;
		VKCall(((PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR"))(instance, &createInfo, 0, &surface));
		assert(surface);
		return surface;
	#else
	#error Unsupported Platform
	#endif
	}

	inline VkFormat getSwapchainFormat(VkPhysicalDevice& pd, VkSurfaceKHR surface) {
		uint32_t formatCount;
		VKCall(vkGetPhysicalDeviceSurfaceFormatsKHR(pd, surface, &formatCount, 0));
		assert(formatCount > 0);
		vector<VkSurfaceFormatKHR> formats(formatCount);
		VKCall(vkGetPhysicalDeviceSurfaceFormatsKHR(pd, surface, &formatCount, formats.data()));
		if (formatCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
			return VK_FORMAT_R8G8B8A8_UNORM;

		for (uint32_t i = 0; i < formatCount; i++)
			if (formats[i].format == VK_FORMAT_R8G8B8A8_UNORM || formats[i].format == VK_FORMAT_B8G8R8A8_UNORM)
				return formats[i].format;

		return formats[0].format;
	}

	inline VkSwapchainKHR createSwapChain(VkPhysicalDevice& pd, VkSurfaceKHR surface, VkFormat format, uint32_t width, uint32_t height, uint32_t* faimlyIndex, VkDevice& device, bool VSyncEnabled) {
		VkSwapchainCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
		VkSurfaceCapabilitiesKHR surfCaps = {};
		VKCall(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pd, surface, &surfCaps));

		createInfo.surface = surface;
		createInfo.minImageCount = surfCaps.minImageCount;
		createInfo.imageFormat = format;
		createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = faimlyIndex;
		createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		createInfo.presentMode = VSyncEnabled ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_IMMEDIATE_KHR;

		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		createInfo.imageExtent.width = width;
		createInfo.imageExtent.height = height;

		VkSwapchainKHR swapChain;
		VKCall(vkCreateSwapchainKHR(device, &createInfo, 0, &swapChain))
		assert(swapChain);
		return swapChain;
	}

	inline VkSemaphore createSemaphore(VkDevice& device) {
		VkSemaphoreCreateInfo createInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
		VkSemaphore vkSemaphore;
		VKCall(vkCreateSemaphore(device, &createInfo, 0, &vkSemaphore));
		assert(vkSemaphore);
		return vkSemaphore;
	}

	inline VkFence createFence(VkDevice& device) {
		VkFenceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		VkFence fence;
		VKCall(vkCreateFence(device, &createInfo, 0, &fence));
		assert(fence);
		return fence;
	}

	inline VkCommandPool createCommandBufferPool(VkDevice& device, uint32_t familyIndex) {
		VkCommandPoolCreateInfo createInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
		createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		createInfo.queueFamilyIndex = familyIndex;
		VkCommandPool commandPool;
		VKCall(vkCreateCommandPool(device, &createInfo, 0, &commandPool));
		assert(commandPool);
		return commandPool;
	}

	inline VkCommandBuffer createCommandBuffer(VkDevice& device, VkCommandPool commandPool) {
		VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
		allocateInfo.commandBufferCount = 1;
		allocateInfo.commandPool = commandPool;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		VkCommandBuffer commandBuffer;
		VKCall(vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer));
		assert(commandBuffer);
		return commandBuffer;
	}

	inline VkRenderPass createRenderPass(VkDevice& device, VkFormat colorFormat, VkFormat depthFormat) {
		VkAttachmentDescription attachments[2] = {};
		attachments[0].flags = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;
		attachments[0].format = colorFormat;
		attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		attachments[1].flags = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;
		attachments[1].format = depthFormat;
		attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference attachmentsRefs[2] = {
			{ 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL },
			{ 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL }
		};

		VkSubpassDescription subpass = {};
		subpass.flags = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX;
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &attachmentsRefs[0];
		subpass.pDepthStencilAttachment = &attachmentsRefs[1];
		subpass.inputAttachmentCount = 0;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo createInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
		createInfo.attachmentCount = 2;
		createInfo.pAttachments = attachments;
		createInfo.subpassCount = 1;
		createInfo.pSubpasses = &subpass;
		createInfo.dependencyCount = 1;
		createInfo.pDependencies = &dependency;

		VkRenderPass renderPass;
		VKCall(vkCreateRenderPass(device, &createInfo, 0, &renderPass));
		assert(renderPass);
		return renderPass;
	}

	inline VkFramebuffer createFrameBuffer(VkDevice& device, VkRenderPass renderPass, VkImageView imageView, VkImageView depthImageView, uint32_t width, uint32_t height) {
		VkImageView attachmentImgViews[2] = {
			imageView,
			depthImageView
		};
		VkFramebufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
		createInfo.renderPass = renderPass;
		createInfo.attachmentCount = 2;
		createInfo.pAttachments = attachmentImgViews;
		createInfo.width = width;
		createInfo.height = height;
		createInfo.layers = 1;
		VkFramebuffer frameBuffer;
		VKCall(vkCreateFramebuffer(device, &createInfo, 0, &frameBuffer));
		assert(frameBuffer);
		return frameBuffer;
	}

	inline VkImageView createImageView(VkDevice& device, VkImage& image, VkFormat format, VkImageAspectFlags aspectFlag) {
		VkImageViewCreateInfo createInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		createInfo.image = image;
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = format;
		createInfo.subresourceRange.aspectMask = aspectFlag;//VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.layerCount = 1;
		VkImageView imageView;
		VKCall(vkCreateImageView(device, &createInfo, 0, &imageView));
		assert(imageView);
		return imageView;
	}

	inline uint32_t findMemoryType(VkPhysicalDevice& pd, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties = {};
		vkGetPhysicalDeviceMemoryProperties(pd, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;

		throw "Failed to find suitable memory type!";
		exit(EXIT_FAILURE);
	}

	inline VulkanBuffer createBuffer(VkPhysicalDevice& pd, VkDevice& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
		VulkanBuffer buffer = {};
		assert(size > 0);
		buffer.size = size;
		VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };

		bufferInfo.size = buffer.size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VKCall(vkCreateBuffer(device, &bufferInfo, 0, &buffer.buffer));
		assert(buffer.buffer);

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, buffer.buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(pd, memRequirements.memoryTypeBits, properties);

		VKCall(vkAllocateMemory(device, &allocInfo, 0, &buffer.memory));
		assert(buffer.memory);

		vkBindBufferMemory(device, buffer.buffer, buffer.memory, 0);
		return buffer;
	}

	inline VkDescriptorPool createDescriptorPool(VkDevice& device) {
		VkDescriptorPoolSize poolSizes[2] = {
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MAX_RENDER_OBJECTS },
				{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MAX_RENDER_OBJECTS }
		};

		VkDescriptorPoolCreateInfo poolInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
		poolInfo.poolSizeCount = 2;
		poolInfo.pPoolSizes = poolSizes;
		poolInfo.maxSets = MAX_RENDER_OBJECTS;
		poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

		VkDescriptorPool descriptorPool;
		VKCall(vkCreateDescriptorPool(device, &poolInfo, 0, &descriptorPool));
		assert(descriptorPool);
		return descriptorPool;
	}

	inline VkDescriptorSet createDescriptorSet(VkDevice& device, VkDescriptorSetLayout& descriptorSetLayout, VkDescriptorPool& descriptorPool, VulkanBuffer& UniformBuffer) {
		VkDescriptorSetAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
		allocInfo.descriptorPool = descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &descriptorSetLayout;

		VkDescriptorSet descriptorSet;
		VKCall(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet));
		assert(descriptorSet);
		return descriptorSet;
	}

	inline void updateDescriptorSet(VkDevice& device, VkDescriptorSet& descriptorSet, VulkanBuffer& UniformBuffer, VkImageView& textureImageView, VkSampler& textureSampler) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = UniformBuffer.buffer;
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = textureImageView;
		imageInfo.sampler = textureSampler;

		VkWriteDescriptorSet descriptorWrite[2] = {};
		descriptorWrite[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite[0].dstSet = descriptorSet;
		descriptorWrite[0].dstBinding = 0;
		descriptorWrite[0].dstArrayElement = 0;
		descriptorWrite[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite[0].descriptorCount = 1;
		descriptorWrite[0].pBufferInfo = &bufferInfo;

		descriptorWrite[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite[1].dstSet = descriptorSet;
		descriptorWrite[1].dstBinding = 1;
		descriptorWrite[1].dstArrayElement = 0;
		descriptorWrite[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrite[1].descriptorCount = 1;
		descriptorWrite[1].pImageInfo = &imageInfo;

		vkUpdateDescriptorSets(device, 2, descriptorWrite, 0, 0);
	}

	inline VkSampler createTextureSampler(VkDevice& device) {
		VkSamplerCreateInfo createInfo = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
		createInfo.magFilter = VK_FILTER_LINEAR;
		createInfo.minFilter = VK_FILTER_LINEAR;
		createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		createInfo.anisotropyEnable = VK_TRUE;
		createInfo.maxAnisotropy = 16.0f;
		createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		createInfo.unnormalizedCoordinates = VK_FALSE;
		createInfo.compareEnable = VK_FALSE;
		createInfo.compareOp = VK_COMPARE_OP_ALWAYS;
		createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

		VkSampler sampler;
		VKCall(vkCreateSampler(device, &createInfo, 0, &sampler));
		assert(sampler);
		return sampler;
	}

	inline VulkanImage createImage(VkPhysicalDevice& pd, VkDevice& device, uint32_t width, uint32_t height, VkFormat format, VkImageAspectFlagBits aspectFlagBit, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties) {
		VulkanImage image = {};
		VkImageCreateInfo imageInfo = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = width;
		imageInfo.extent.height = height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VKCall(vkCreateImage(device, &imageInfo, 0, &image.image));

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(device, image.image, &memRequirements);

		VkMemoryAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(pd, memRequirements.memoryTypeBits, properties);

		VKCall(vkAllocateMemory(device, &allocInfo, 0, &image.memory));

		vkBindImageMemory(device, image.image, image.memory, 0);

		image.imgView = createImageView(device, image.image, format, aspectFlagBit);

		return image;
	}

	inline void destroyVulkanImage(VkDevice& device, VulkanImage& image) {
		vkDestroyImage(device, image.image, 0);
		vkDestroyImageView(device, image.imgView, 0);
		vkFreeMemory(device, image.memory, 0);
	}

	inline VkCommandBuffer singleInstanceCommandBuffer(VkDevice& device, VkCommandPool& commandPool) {
		auto commandBuffer = createCommandBuffer(device, commandPool);
		VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		VKCall(vkBeginCommandBuffer(commandBuffer, &beginInfo));
		return commandBuffer;
	}

	inline VkCommandBuffer singleInstanceCommandBufferWRP(VkDevice& device, VkCommandPool& commandPool, VkRenderPass& renderPass, VkFramebuffer& frameBuffer) {
		auto commandBuffer = createCommandBuffer(device, commandPool);
		VkCommandBufferInheritanceInfo inheritanceInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO };
		inheritanceInfo.renderPass = renderPass;
		inheritanceInfo.framebuffer = frameBuffer;
		VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
		beginInfo.pInheritanceInfo = &inheritanceInfo;
		VKCall(vkBeginCommandBuffer(commandBuffer, &beginInfo));
		return commandBuffer;
	}

	inline void endSingleInstanceCommandBuffer(VkDevice& device, VkCommandPool& commandPool, VkCommandBuffer& commandBuffer, VkQueue& queue) {
		vkEndCommandBuffer(commandBuffer);
		VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		VKCall(vkQueueSubmit(queue, 1, &submitInfo, 0));
		VKCall(vkQueueWaitIdle(queue));
		vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
	}

	inline void endSingleInstanceCommandBufferWithSync(VkDevice& device, VkCommandPool& commandPool, VkCommandBuffer& commandBuffer, VkQueue& queue, VkSemaphore& aquireSemaphore, VkSemaphore& releaseSemaphore, VkFence& fence) {
		vkEndCommandBuffer(commandBuffer);
		VkPipelineStageFlags submitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &aquireSemaphore;
		submitInfo.pWaitDstStageMask = &submitStageMask;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &releaseSemaphore;
		vkResetFences(device, 1, &fence);
		VKCall(vkQueueSubmit(queue, 1, &submitInfo, fence));
		VKCall(vkQueueWaitIdle(queue));
		vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
	}

	inline void copyBufferToImage(VkDevice& device, VkCommandPool& commandPool, VkQueue& queue, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
		auto commandBuffer = singleInstanceCommandBuffer(device, commandPool);

		VkBufferImageCopy region = {};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;
		region.imageOffset = {0, 0, 0};
		region.imageExtent = {
			width,
			height,
			1
		};

		vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

		endSingleInstanceCommandBuffer(device, commandPool, commandBuffer, queue);
	}

	inline void transitionImageLayout(VkDevice& device, VkCommandPool& commandPool, VkQueue& queue, VkImage& image, VkImageAspectFlags bitflag, VkImageLayout oldLayout, VkImageLayout newLayout) {
		auto commandBuffer = singleInstanceCommandBuffer(device, commandPool);

		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = oldLayout;
		barrier.newLayout = newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = image;
		barrier.subresourceRange.aspectMask = bitflag;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		} else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		} else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		} else {
			throw invalid_argument("unsupported layout transition!");
		}

		vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, 0, 0, 0, 1, &barrier);

		endSingleInstanceCommandBuffer(device, commandPool, commandBuffer, queue);
	}

	inline void updateSwapchain(
		VkSwapchainKHR& swapchain,
		VkPhysicalDevice& pd,
		VkDevice& device,
		VkSurfaceKHR& surface,
		uint32_t& familyIndex,
		vector<VkImage>& SwapChainImages,
		vector<VkImageView>& SwapChainImageViews,
		vector<VkFramebuffer>& SwapChainFrameBuffers,
		VkFormat& format,
		VkRenderPass& RenderPass,
		VkFormat& depthFormat,
		VulkanImage& depthImage,
		VkCommandPool& commandPool,
		VkQueue& queue,
		uint32_t newWidth,
		uint32_t newHeight) {
		uint32_t SCImageCount;
		if(swapchain != VK_NULL_HANDLE)
			vkDestroySwapchainKHR(device, swapchain, 0);
		if(SwapChainImageViews.size() > 0)
			for(auto& SwapChainImageView : SwapChainImageViews)
				vkDestroyImageView(device, SwapChainImageView, 0);

		if(SwapChainFrameBuffers.size() > 0)
			for(auto& SwapChainFrameBuffer : SwapChainFrameBuffers)
				vkDestroyFramebuffer(device, SwapChainFrameBuffer, 0);

		destroyVulkanImage(device, depthImage);

		swapchain = createSwapChain(pd, surface, format, newWidth, newHeight, &familyIndex, device, G_VSYNC);
		VKCall(vkGetSwapchainImagesKHR(device, swapchain, &SCImageCount, 0));
		SwapChainImages.clear();
		SwapChainImages.resize(SCImageCount);
		VKCall(vkGetSwapchainImagesKHR(device, swapchain, &SCImageCount, SwapChainImages.data()));
		SwapChainImageViews.clear();
		SwapChainImageViews.resize(SCImageCount);
		for(uint32_t i = 0; i < SwapChainImageViews.size(); i++)
			SwapChainImageViews[i] = createImageView(device, SwapChainImages[i], format, VK_IMAGE_ASPECT_COLOR_BIT);

		depthImage = createImage(pd, device, newWidth, newHeight, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		transitionImageLayout(device, commandPool, queue, depthImage.image, VK_IMAGE_ASPECT_DEPTH_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

		SwapChainFrameBuffers.clear();
		SwapChainFrameBuffers.resize(SCImageCount);
		for(uint32_t i = 0; i < SwapChainFrameBuffers.size(); i++)
			SwapChainFrameBuffers[i] = createFrameBuffer(device, RenderPass, SwapChainImageViews[i], depthImage.imgView, newWidth, newHeight);
	}

	inline VkPipelineCache createPipelineCache(VkDevice& device) {
		VkPipelineCacheCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO };
		VkPipelineCache pipelineCache;
		VKCall(vkCreatePipelineCache(device, &createInfo, 0, &pipelineCache));
		assert(pipelineCache);
		return pipelineCache;
	}

	inline VkPipelineLayout createPipelineLayout(VkDevice& device, VkDescriptorSetLayout& dsl) {
		VkPipelineLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
		createInfo.setLayoutCount = 1;
		createInfo.pSetLayouts = &dsl;

		VkPipelineLayout pipelineLayout;
		VKCall(vkCreatePipelineLayout(device, &createInfo, 0, &pipelineLayout));
		assert(pipelineLayout);
		return pipelineLayout;
	}

	inline VkPipeline createGraphicsPipeline(VkDevice& device, VkPipelineCache& cache, VkPipelineLayout& layout, VkRenderPass& renderPass, VkShaderModule& vs, VkShaderModule& fs, VkViewport& viewport, VkRect2D& scissor, VkDescriptorSetLayout& dsl, VkPrimitiveTopology topology) {
		VkGraphicsPipelineCreateInfo createInfo = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };

		VkPipelineShaderStageCreateInfo stages[2] = {};

		// Vertex
		stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		stages[0].module = vs;
		stages[0].pName = "main";

		// Fragment
		stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		stages[1].module = fs;
		stages[1].pName = "main";

		createInfo.stageCount = 2;
		createInfo.pStages = stages;

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

		auto bindingDescription = Vertex::getBindingDescription();
		auto attributeDescriptions = Vertex::getAttributeDescriptions();

		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
		createInfo.pVertexInputState = &vertexInputInfo;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
		inputAssembly.topology = topology;
		createInfo.pInputAssemblyState = &inputAssembly;

		VkPipelineViewportStateCreateInfo viewportState = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;
		createInfo.pViewportState = &viewportState;

		VkPipelineRasterizationStateCreateInfo rasterizer = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
	#if 0
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	#else
		rasterizer.cullMode = VK_CULL_MODE_NONE;
	#endif
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		createInfo.pRasterizationState = &rasterizer;

		VkPipelineMultisampleStateCreateInfo multisampling = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		createInfo.pMultisampleState = &multisampling;

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.blendEnable = true;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.colorWriteMask =
				VK_COLOR_COMPONENT_R_BIT |
				VK_COLOR_COMPONENT_G_BIT |
				VK_COLOR_COMPONENT_B_BIT |
				VK_COLOR_COMPONENT_A_BIT;

		VkPipelineColorBlendStateCreateInfo colorBlending = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0;
		colorBlending.blendConstants[1] = 0;
		colorBlending.blendConstants[2] = 0;
		colorBlending.blendConstants[3] = 0;
		createInfo.pColorBlendState = &colorBlending;

		createInfo.layout = layout;

		createInfo.renderPass = renderPass;

		VkPipelineDepthStencilStateCreateInfo depthStencilState = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
		depthStencilState.depthTestEnable = true;
		depthStencilState.depthWriteEnable = true;
		depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencilState.depthBoundsTestEnable = VK_FALSE;
		depthStencilState.minDepthBounds = 0.0f;
		depthStencilState.maxDepthBounds = 1.0f;
		depthStencilState.stencilTestEnable = VK_FALSE;
		depthStencilState.front = {};
		depthStencilState.back = {};
		createInfo.pDepthStencilState = &depthStencilState;

		VkDynamicState dynamicStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR, VK_DYNAMIC_STATE_LINE_WIDTH};

		VkPipelineDynamicStateCreateInfo dynamicState = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
		dynamicState.dynamicStateCount = 3;
		dynamicState.pDynamicStates = dynamicStates;
		createInfo.pDynamicState = &dynamicState;

		VkPipeline pipeline;
		VKCall(vkCreateGraphicsPipelines(device, cache, 1, &createInfo, 0, &pipeline));
		assert(pipeline);
		return pipeline;
	}

	inline void destroyVulkanBuffer(VkDevice& device, VulkanBuffer& vulkanBuffer) {
		vkDestroyBuffer(device, vulkanBuffer.buffer, 0);
		vkFreeMemory(device, vulkanBuffer.memory, 0);
	}

	inline VkDescriptorSetLayout createDescriptorSetLayout(VkDevice& device) {
		VkDescriptorSetLayoutBinding layoutBindings[2] = {};

		layoutBindings[0].binding = 0;
		layoutBindings[0].descriptorCount = 1;
		layoutBindings[0].descriptorType =  VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		layoutBindings[1].binding = 1;
		layoutBindings[1].descriptorCount = 1;
		layoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		layoutBindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		VkDescriptorSetLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
		createInfo.bindingCount = 2;
		createInfo.pBindings = layoutBindings;

		VkDescriptorSetLayout descriptorSetLayout;
		VKCall(vkCreateDescriptorSetLayout(device, &createInfo, 0, &descriptorSetLayout));
		assert(descriptorSetLayout);
		return descriptorSetLayout;
	}

	inline VulkanVertexPipeline createVulkanVertexPipeline(VkDevice& device, VkDescriptorSetLayout& descriptorSetLayout, VkRenderPass& renderPass, VkShaderModule& vs, VkShaderModule& fs, VkViewport& viewport, VkRect2D& scissor, VkPrimitiveTopology topology) {
		VulkanVertexPipeline pipeline = {};
		pipeline.layout = createPipelineLayout(device, descriptorSetLayout);
		pipeline.cache = createPipelineCache(device);
		pipeline.pipeline = createGraphicsPipeline(device, pipeline.cache, pipeline.layout, renderPass, vs, fs, viewport, scissor, descriptorSetLayout, topology);
		return pipeline;
	}

	inline void destroyVulkanVertexPipeline(VkDevice& device, VulkanVertexPipeline& pipeline) {
		vkDestroyPipelineLayout(device, pipeline.layout, 0);
		vkDestroyPipelineCache(device, pipeline.cache, 0);
		destroyVulkanBuffer(device, pipeline.vertexBuffer);
		vkDestroyPipeline(device, pipeline.pipeline, 0);
	}

	inline VulkanIndexPipeline createVulkanIndexPipeline(VkDevice& device, VkDescriptorSetLayout& descriptorSetLayout, VkRenderPass& renderPass, VkShaderModule& vs, VkShaderModule& fs, VkViewport& viewport, VkRect2D& scissor, VkPrimitiveTopology topology) {
		VulkanIndexPipeline pipeline = {};
		pipeline.layout = createPipelineLayout(device, descriptorSetLayout);
		pipeline.cache = createPipelineCache(device);
		pipeline.pipeline = createGraphicsPipeline(device, pipeline.cache, pipeline.layout, renderPass, vs, fs, viewport, scissor, descriptorSetLayout, topology);
		return pipeline;
	}

	inline void copyBuffer(VkDevice& device, VkCommandPool& commandPool, VkQueue& queue, VkBuffer& srcBuffer, VkBuffer& dstBuffer, VkDeviceSize size) {
		auto commandBuffer = singleInstanceCommandBuffer(device, commandPool);

		VkBufferCopy copyRegion = { 0, 0, size };
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

		endSingleInstanceCommandBuffer(device, commandPool, commandBuffer, queue);
	}

	template<typename T>
	inline void VulkanMemoryDataMapping(VkDevice& device, VulkanBuffer& buffer, T* data) {
		vkMapMemory(device, buffer.memory, 0, buffer.size, 0, &buffer.data);
		memcpy(buffer.data, data, buffer.size);
		vkUnmapMemory(device, buffer.memory);
	}

	inline VulkanBuffer createVertexBuffer(VkPhysicalDevice& pd, VkDevice& device, VkCommandPool& commandPool, VkQueue& queue, vector<Vertex>& vertices) {
		VulkanBuffer stagingBuffer = createBuffer(pd, device, vertices.size() * sizeof(Vertex), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		VulkanMemoryDataMapping(device, stagingBuffer, vertices.data());

		VulkanBuffer vertexBuffer = createBuffer(pd, device, vertices.size() * sizeof(Vertex), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		copyBuffer(device, commandPool, queue, stagingBuffer.buffer, vertexBuffer.buffer, vertices.size() * sizeof(Vertex));

		destroyVulkanBuffer(device, stagingBuffer);

		return vertexBuffer;
	}

	inline void destroyVulkanIndexPipeline(VkDevice& device, VulkanIndexPipeline& pipeline) {
		vkDestroyPipelineLayout(device, pipeline.layout, 0);
		vkDestroyPipelineCache(device, pipeline.cache, 0);
		destroyVulkanBuffer(device, pipeline.vertexBuffer);
		destroyVulkanBuffer(device, pipeline.indexBuffer);
		vkDestroyPipeline(device, pipeline.pipeline, 0);
	}

	inline VkFormat findSupportedFormat(VkPhysicalDevice& pd, const vector<VkFormat>&& candidates, VkImageTiling&& tiling, VkFormatFeatureFlags&& features) {
		for(auto& format : candidates) {
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(pd, format, &props);

			if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
				return format;
			else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
				return format;
		}
		assert(!"No supported formats!");
		return VK_FORMAT_UNDEFINED;
	}

	inline VkFormat findDepthFormat(VkPhysicalDevice& pd) {
		return findSupportedFormat(
			pd,
			{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
		);
	}

	inline bool hasStencilComponent(VkFormat& format) {
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}
}
#endif