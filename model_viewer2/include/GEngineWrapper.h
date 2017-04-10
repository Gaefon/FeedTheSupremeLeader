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
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <string>

namespace GEngine
{
    class GEngineWrapper
    {

        public:
        GEngineWrapper(Window *window);
        ~GEngineWrapper();

        void startDrawing();
        Engine *getEngine();

        private:
        Engine *g_engine;
        Window *g_window;
        Surface *g_surface;
        PhysicalDevice *g_physical_device;
        SwapChain *g_swapchain;
        Pipeline *g_pipeline;
        CommandBuffers *g_command_buffers;
        RenderPass *g_render_pass;
        Shader *g_shader_vert;
        Shader *g_shader_frag;

        void init();
        void initEngine(std::string engineName);
        void initDevices();
        void initSwapChain();
        void initRenderPass();
        void initPipeline();
        void initCmdBuffers();
        void createPipeline(Vertex *vertex);
        void startRecording();
        void initGetAndDisplayDevices();
    };
}
#endif // GENGINEWRAPPER_H_INCLUDED
