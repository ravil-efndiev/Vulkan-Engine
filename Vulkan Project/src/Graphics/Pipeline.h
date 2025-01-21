#pragma once
#include <Vulkan/Device.h>
#include <Vulkan/Swapchain.h>
#include "Shader.h"
#include "RenderPass.h"

namespace cp {
	struct PipelineConfiguration {
		enum VertexType {
			PositionColorVertex,
			TexCoordVertex,
			MeshVertex,
		};

		VertexType vertexType = PositionColorVertex;
	};

	class Pipeline {
	public:
		Pipeline(Device& device, Swapchain& swapchain, const PipelineConfiguration& config = {});
		~Pipeline();

		void setShaderStages(const Shader& shaderModules);
		void create();

		VkPipeline vkHandle() const { return mPipeline; }

	private:
		void setFixedState();

	private:
		PipelineConfiguration mConfig;

		Device& mDevice;
		Swapchain& mSwapchain;
		VkPipeline mPipeline = VK_NULL_HANDLE;
		VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;
		RenderPass mRenderPass{ mDevice, mSwapchain };

		VkPipelineShaderStageCreateInfo mVertexShaderStage{};
		VkPipelineShaderStageCreateInfo mFragmentShaderStage{};
		VkPipelineDynamicStateCreateInfo mDynamicState{};
		VkPipelineInputAssemblyStateCreateInfo mInputAssembly{};
		VkPipelineVertexInputStateCreateInfo mVertexInput{};
		VkPipelineViewportStateCreateInfo mViewportState{};
		VkPipelineRasterizationStateCreateInfo mRasterizer{};
		VkPipelineMultisampleStateCreateInfo mMultisampleState{};
		VkPipelineColorBlendStateCreateInfo mColorBlending{};

		const std::array<VkDynamicState, 2> mDynamicStates = { VK_DYNAMIC_STATE_SCISSOR, VK_DYNAMIC_STATE_VIEWPORT };
		VkViewport mBaseViewport{};
		VkRect2D mScissor{};
		VkPipelineColorBlendAttachmentState mColorBlendAttachment{};
	};
}