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
