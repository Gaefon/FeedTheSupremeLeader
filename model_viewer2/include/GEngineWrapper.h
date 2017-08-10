#ifndef GENGINEWRAPPER_H_INCLUDED
#define GENGINEWRAPPER_H_INCLUDED

#include <GEngine.h>
#include <Version.h>
#include <Window.h>
#include <Surface.h>
#include <SwapChain.h>
#include <Shader.h>
#include <Pipeline.h>
#include <VertexBufferData.h>
#include <buffers/CommandBuffers.h>
#include <buffers/UniformBuffer.h>
#include <DepthTest.h>
#include <Camera.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace GEngine
{
	class GEngineWrapper
	{

		public:
			GEngineWrapper(Window *window);
			~GEngineWrapper();

			void beginCommandBufferAndRenderPass();
			void startRecording(Pipeline *pipeline, std::vector<VertexBufferData> vertices, std::vector<uint16_t> indexes, Camera *camera);
			void endCommandBufferAndRenderPass();
			void startDrawing();
			Engine *getEngine();
			Window *getWindow();
			SwapChain *getSwapchain();
			RenderPass *getRenderPass();

		private:
			Engine *g_engine;
			Window *g_window;
			Surface *g_surface;
			PhysicalDevice *g_physical_device;
			SwapChain *g_swapchain;
			DepthTest *g_depth_test;
			CommandBuffers *g_command_buffers;
			RenderPass *g_render_pass;
			Framebuffers *g_framebuffers;
			std::vector<VertexBufferData> vertices;
			std::vector<uint16_t> indexes;

			void init();
			void initEngine(std::string engineName);
			void initDevices();
			void initSwapChain();
			void initDepthTest();
			void initRenderPass();
			void initCmdBuffers();
			void initFrameBuffers();
	};
}
#endif // GENGINEWRAPPER_H_INCLUDED
