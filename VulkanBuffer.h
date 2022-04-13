/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

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
