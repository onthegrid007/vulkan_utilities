/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

#ifndef VULKANIMAGE_H_
#define VULKANIMAGE_H_
namespace VulkanUtilities {
	typedef struct {
		VkImage image;
		VkImageView imgView;
		VkImageLayout layout;
		VkDeviceMemory memory;
		VkDescriptorImageInfo descriptor;
	} VulkanImage;
}
#endif