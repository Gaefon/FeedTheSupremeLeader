#include <GEngineWrapper.h>
using namespace std;

namespace GEngine
{
    GEngineWrapper::GEngineWrapper(Window *window)
    {
        g_window = window;
        init();
    }

    GEngineWrapper::~GEngineWrapper()
    {
        delete g_command_buffers;
        delete g_pipeline;
        delete g_shader_vert;
        delete g_shader_frag;
        delete g_render_pass;
        delete g_swapchain;
        delete g_surface;
        delete g_engine;
    }

    void GEngineWrapper::init()
    {
        initEngine("test");
        initDevices();
        initSwapChain();
        initRenderPass();
        initPipeline();
        Vertex *vertex = new Vertex({0.0f, -0.5f}, {1.0f, 0.0f, 0.0f});
        createPipeline(vertex);
        initCmdBuffers();
        startRecording();
    }

    void GEngineWrapper::initEngine(string engine_name)
    {
        g_engine = new Engine();
        g_engine->enableValidationLayers();
        g_engine->init(engine_name, Version::makeVersion(1, 0, 0));
        g_engine->addExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        g_engine->pickPhysicalDevices();
    }

    void GEngineWrapper::initDevices()
    {
        g_surface = new Surface(g_engine, g_window);
        g_physical_device = g_surface->getSuitableDevice(g_engine);
        g_engine->createLogicalDevice(g_physical_device);
    }

    void GEngineWrapper::initSwapChain()
    {
        g_swapchain = new SwapChain(g_engine->getLogicalDevice());
        g_swapchain->createSwapChain(g_surface, g_window, g_physical_device);
        g_swapchain->initImageViews();
    }

    void GEngineWrapper::initRenderPass()
    {
        g_render_pass = new RenderPass(g_engine->getLogicalDevice());
        g_render_pass->initRenderPass(g_swapchain);

    }

    void GEngineWrapper::initPipeline()
    {
        g_shader_frag = new Shader(string("Shaders/2d_dummy.frag"), string("main"), g_engine->getLogicalDevice());
        g_shader_vert = new Shader(string("Shaders/2d_dummy.vert"), string("main"), g_engine->getLogicalDevice());
        g_pipeline = new Pipeline(g_engine->getLogicalDevice());
    }

    void GEngineWrapper::initCmdBuffers()
    {
        g_command_buffers = new CommandBuffers(g_engine->getLogicalDevice());
    }

    void GEngineWrapper::createPipeline(Vertex *vertex)
    {
       g_pipeline->setVertexInput(vertex);
       g_pipeline->setInputAssembler();
       g_pipeline->setVertexShader(g_shader_vert);
       g_pipeline->setFragmentShader(g_shader_frag);

       g_pipeline->setViewPort(g_window->getWidth(), g_window->getHeight());
       g_pipeline->setScissor(g_swapchain->getExtent());
       g_pipeline->createViewportStateInfos();

       g_pipeline->setRasterizerInfos();
       g_pipeline->setMultisamplingInfos();
       g_pipeline->setColorBlendAttachment();
       g_pipeline->createDynamicStateInfos();
       g_pipeline->createPipelineLayout();
       g_pipeline->createPipeline(g_render_pass);

       g_pipeline->initFramebuffers(g_swapchain, g_render_pass);
    }

    void GEngineWrapper::startRecording()
    {
        g_command_buffers->createCommandPool(g_physical_device);
        g_command_buffers->createCommandBuffers(g_pipeline->getFramebuffers());
        g_command_buffers->startRecording(g_pipeline->getFramebuffers(), g_swapchain, g_render_pass, g_pipeline);
    }

    Engine *GEngineWrapper::getEngine()
    {
        return g_engine;
    }

    void GEngineWrapper::startDrawing()
    {
        g_command_buffers->draw(g_swapchain);
    }
}
