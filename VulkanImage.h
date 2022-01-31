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
