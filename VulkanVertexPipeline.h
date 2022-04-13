/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

#ifndef VULKANVERTEXPIPELINE_H_
#define VULKANVERTEXPIPELINE_H_

typedef struct VulkanVertexPipeline_t {
	VkPipeline pipeline;
	VkPipelineCache cache;
	VkPipelineLayout layout;
//	VkDescriptorSetLayout descriptorSetLayout;
	VulkanBuffer vertexBuffer;
} VulkanVertexPipeline;

#endif
