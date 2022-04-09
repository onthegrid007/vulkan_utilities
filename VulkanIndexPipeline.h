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
