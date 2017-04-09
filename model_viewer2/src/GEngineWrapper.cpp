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
        delete g_render_pass;
        delete g_shader_vert;
        delete g_shader_frag;
        delete g_swapchain;
        delete g_physical_device;
        delete g_device;
        delete g_engine;
        delete g_surface;
    }

    void GEngineWrapper::init()
    {
        initEngine("test");
        initDevices();
        initSwapChain();
        initRenderPass();
        initPipeline();
        initCmdBuffers();
        initGetAndDisplayDevices();
        createPipeline();
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

    void GEngineWrapper::initGetAndDisplayDevices()
    {
        list<PhysicalDevice *> devs = g_engine->getListPhysicalDevices();
        for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
        {
            cout << (*i)->getDeviceName() << endl;
            cout << "0x" << hex << (*i)->getVendorId() << endl;
            cout << "0x" << hex << (*i)->getDeviceId() << endl;
            cout << Version::versionToString((*i)->getApiVersion()) << endl;
            cout << Version::versionToString((*i)->getDriverVersion()) << endl;
        }

    }

    void GEngineWrapper::initDevices()
    {
        g_surface = new Surface(g_engine, g_window);
        g_physical_device = g_surface->getSuitableDevice(g_engine);
        g_engine->createLogicalDevice(g_physical_device);
        g_device = g_engine->getLogicalDevice();
    }

    void GEngineWrapper::initSwapChain()
    {
        g_swapchain = new SwapChain(g_device);
        g_swapchain->createSwapChain(g_surface, g_window, g_physical_device);
        g_swapchain->initImageViews();
    }

    void GEngineWrapper::initRenderPass()
    {
        g_render_pass = new RenderPass(g_device);
        g_shader_frag = new Shader(string("Shaders/2d_dummy.frag"), string("main"), g_device);
        g_shader_vert = new Shader(string("Shaders/2d_dummy.vert"), string("main"), g_device);
        g_render_pass->initRenderPass(g_swapchain);

    }

    void GEngineWrapper::initPipeline()
    {
        g_pipeline = new Pipeline(g_device);
    }

    void GEngineWrapper::initCmdBuffers()
    {
        g_command_buffers = new CommandBuffers(g_device);
    }

    void GEngineWrapper::createPipeline()
    {
       g_pipeline->setVertexInput();
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

    Device GEngineWrapper::getDevice()
    {
        return *g_device;
    }

    /*CommandBuffers GEngineWrapper::getCmdBuffers()
    {
        return *g_command_buffers;
    }*/

    void GEngineWrapper::startDrawing()
    {
        g_command_buffers->draw(g_swapchain);
    }
}
