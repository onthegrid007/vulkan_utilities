/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

#ifndef VULKANINDEXPIPELINE_H_
#define VULKANINDEXPIPELINE_H_

typedef struct {
	VkPipeline pipeline;
	VkPipelineLayout layout;
	VkPipelineCache cache;
	VulkanBuffer vertexBuffer;
	VulkanBuffer indexBuffer;
} VulkanIndexPipeline;

#endif
