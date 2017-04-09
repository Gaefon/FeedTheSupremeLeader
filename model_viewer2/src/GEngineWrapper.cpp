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
        delete g_engine;
        delete g_window;
        delete g_device;
        delete g_surface;
        delete g_physical_device;
        delete g_swapchain;
        delete g_pipeline;
        delete g_command_buffers;
        delete g_render_pass;
        delete g_shader_vert;
        delete g_shader_frag;
    }

    void GEngineWrapper::init()
    {
        initEngine("test");
        initDevices();
        initSwapChain();
        initRenderPass();
        initPipeline();
        initCmdBuffers();

        list<PhysicalDevice *> devs = g_engine->getListPhysicalDevices();
        for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
        {
            cout << (*i)->getDeviceName() << endl;
            cout << "0x" << hex << (*i)->getVendorId() << endl;
            cout << "0x" << hex << (*i)->getDeviceId() << endl;
            cout << Version::versionToString((*i)->getApiVersion()) << endl;
            cout << Version::versionToString((*i)->getDriverVersion()) << endl;
        }

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

    void GEngineWrapper::initDevices()
    {
        Surface surface(g_engine, g_window);
        PhysicalDevice *phys_dev = surface.getSuitableDevice(g_engine);
        g_engine->createLogicalDevice(phys_dev);
        g_device = g_engine->getLogicalDevice();
        g_physical_device = phys_dev;
        g_surface = &surface;
    }

    void GEngineWrapper::initSwapChain()
    {
        SwapChain swap_chain(g_device);
        swap_chain.createSwapChain(g_surface, g_window, g_physical_device);
        swap_chain.initImageViews();
    }

    void GEngineWrapper::initRenderPass()
    {
        RenderPass render_pass(g_device);
        Shader shader_frag(string("Shaders/2d_dummy.frag"), string("main"), g_device);
        Shader shader_vert(string("Shaders/2d_dummy.vert"), string("main"), g_device);
        g_shader_frag = &shader_frag;
        g_shader_vert = &shader_vert;
        render_pass.initRenderPass(g_swapchain);
        g_render_pass = &render_pass;
    }

    void GEngineWrapper::initPipeline()
    {
        Pipeline pipeline(g_device);
        g_pipeline = &pipeline;
    }

    void GEngineWrapper::initCmdBuffers()
    {
        CommandBuffers cmd_buffers(g_device);
        g_command_buffers = &cmd_buffers;
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
