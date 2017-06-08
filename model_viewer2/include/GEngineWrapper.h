#ifndef GENGINEWRAPPER_H_INCLUDED
#define GENGINEWRAPPER_H_INCLUDED

#include <GEngine.h>
#include <Version.h>
#include <Window.h>
#include <Surface.h>
#include <SwapChain.h>
#include <Shader.h>
#include <Pipeline.h>
#include <Vertex.h>
#include <CommandBuffers.h>
#include <VertexBuffer.h>
#include <StagingBuffer.h>
#include <IndexBuffer.h>
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

			void startRecording(Pipeline *pipeline, std::vector<Vertex> vertices, std::vector<uint16_t> indexes);
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
			CommandBuffers *g_command_buffers;
			RenderPass *g_render_pass;
			StagingBuffer *g_staging_buffer;
			StagingBuffer *g_staging_buffer2;
			VertexBuffer *g_vertex_buffer;
			IndexBuffer *g_index_buffer;

			void init();
			void initEngine(std::string engineName);
			void initDevices();
			void initSwapChain();
			void initRenderPass();
			void initCmdBuffers();
	};
}
#endif // GENGINEWRAPPER_H_INCLUDED
