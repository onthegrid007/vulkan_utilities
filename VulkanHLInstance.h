#ifndef VULKAHLINSTANCE_H
#define VULKAHLINSTANCE_H

#include "common.h"

namespace VulkanUtilities {
    class VulkanHLInstance {
        public:
        VulkanHLinstance();
        VkResult Instantiation(std::vector<std::string>& deviceExtensions);
        void DestroySafely();
        ~VulkanHLinstance();

        private:
        char m_instantiationState;
        VkInstance m_instance;
        VkSurface m_surface;
        std::vector<std::string> m_deviceExtensions = { 
            #ifdef VULKAN_PLATFORM_WINDOWS
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            #else
            #error Unsupported Platform
            #endif
        };
        VkPhysicalDevice m_pd;
        uint32_t m_familyIndex;
        VkFormat m_scFormat;
        VkFormat m_depthFormat;
        VkDevice m_device;
        VkCommandPool m_cPool;
        VkRenderPass m_rp;
        VkQueue m_queue;
        VkDescriptorSetLayout m_dSetLayout;
        VkDescriptorPool m_dPool;
        VkFence m_fence;
        VkSemaphore m_aquireSemaphore;
        VkSemaphore m_releaseSemaphore;

        VkSwapchainKHR m_sc;


        std::vector<VkImage> m_scImages;
        std::vector<VkImageView> m_scImageViews;
        std::vector<VkFramebuffer> m_scFrameBuffers;
        uint32_t m_scImageCount;
        VkCommandBuffer m_cBuffer;
        VkViewport m_viewport;
        VkRect2D m_scissor;
        VulkanImage m_depthImg;
        VkImageView m_depthImgView;
    };
}

#endif
