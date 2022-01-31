#ifndef VULKANBUFFER_H_
#define VULKANBUFFER_H_

namespace VulkanUtilities {
    typedef struct {
        VkBuffer buffer;
        VkDeviceMemory memory;
        void* data;
        VkDeviceSize size;
    } VulkanBuffer;
}
#endif
