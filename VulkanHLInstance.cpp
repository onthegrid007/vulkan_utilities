/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

#include "VulkanHLInstance.h"

namespace VulkanUtilities {
        VulkanHLInstance::VulkanHLinstance() {

        }

        VkResult VulkanHLInstance::Instantiation(std::vector<std::string>& deviceExtensions) {
            if(m_instantionState < 0 || m_instantionState == 1) {
                cout < "Something went wrong with the previous instantiation this VulkanHLInstance.\n";
                cout << "Please run the DestroyInstance member function to cleanup this Instance.\n";
                return VkFailure;
            }
            else if(m_instantionState > 1) {
                cout << "This VulkanHLInstance object has already been instantiated!" << endl;
                cout << "To destroy this instance, run Destroy as a membber function on the object." << endl;
                return VkFailed;
            }

            m_instantionState = 1;
	        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            m_instance = createInstance();
            m_surface = createSurface(m_instance, m_window);
            m_pd = getPhysicalDevice(m_Instance, m_deviceExtensions, m_surface);
            m_familyIndex = getGraphicsQueueFamily(m_pd);
            m_scFormat = getSwapchainFormat(m_surface, m_pd);
            m_depthFormat = findDepthFormat(m_pd);
            m_device = createDevice(m_pd, m_deviceExtensions, m_familyIndex);
            m_cPool = createCommandBufferPool(m_device, m_familyIndex);
            m_rp = createRenderPass(m_scFormat, m_depthFormat, m_device);
            vkGetDeviceQueue(m_device, m_familyIndex, 0, &m_queue);
            m_dSetLayout = createDescriptorSetLayout(m_device);
            m_dPool = createDescriptorPool(m_device);
            m_fence = createFence(m_device);
            m_aquireSemaphore = createSemaphore(m_device);
            m_releaseSemaphore = createSemaphore(m_device);
            #ifdef VULKAN_PLATFORM_WINDOWS
                m_sc = createSwapChain<VkSwapchainKHR>(m_pd, m_surface, m_scFormat, ice)
            #else
            #error Unsupported Platform
            #endif
        }

        void DestroySafely() {
            vkDestroyFence(m_VkDevice, m_VkFence, 0);
            destroyVulkanImage(m_VkDevice, m_VkDepthImage);
            vkDestroyDescriptorPool(m_VkDevice, m_VkDescriptorPool, 0);
            vkDestroyDescriptorSetLayout(m_VkDevice, m_VkDescriptorSetLayout, 0);
            vkDestroyCommandPool(m_VkDevice, m_VkCommandPool, 0);
            vkDestroyRenderPass(m_VkDevice, m_VkRenderPass, 0);
            vkDestroySemaphore(m_VkDevice, m_VkReleaseSemaphore, 0);
            vkDestroySemaphore(m_VkDevice, m_VkAquireSemaphore, 0);
            for(uint32_t i = 0; i < m_VkSwapChainFrameBuffers.size(); i++)
                vkDestroyFramebuffer(m_VkDevice, m_VkSwapChainFrameBuffers[i], 0);
            for(uint32_t i = 0; i < m_VkSwapChainImageViews.size(); i++)
                vkDestroyImageView(m_VkDevice, m_VkSwapChainImageViews[i], 0);
            vkDestroySwapchainKHR(m_VkDevice, m_VkSwapChain, 0);
            vkDestroyDevice(m_VkDevice, 0);
            vkDestroySurfaceKHR(m_VkInstance, m_VkSurface, 0);
            vkDestroyInstance(m_VkInstance, 0);
        }
        ~VulkanHLinstance();
}

std::vector<std::string> m_deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        }