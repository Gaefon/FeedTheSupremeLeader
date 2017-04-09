#include <GEngineWrapper.h>

using namespace std;

namespace GEngine
{
    GEngineWrapper::GEngineWrapper(){}
    GEngineWrapper::~GEngineWrapper(){}

    GEngineWrapper::Draw(string win_name, unsigned int win_width, unsigned int win_height)
    {
        Window *window;
        list<string> extensions;

        glfwInit();

        window = new Window(win_name, win_width, win_height);

        Engine engine;
        engine.enableValidationLayers();
        engine.init("test", Version::makeVersion(1, 0, 0));
        engine.addExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        engine.pickPhysicalDevices();

        // mettre la creation de surface et device vituelle dans la classe Engine (?)
        Surface surface(&engine, window);
        PhysicalDevice *phys_dev = surface.getSuitableDevice(&engine);
        engine.createLogicalDevice(phys_dev);
        Device *dev = engine.getLogicalDevice();


        SwapChain swap_chain(dev);

        swap_chain.createSwapChain(&surface, window, phys_dev);
        swap_chain.initImageViews();

        Shader shader_frag(string("Shaders/2d_dummy.frag"), string("main"), dev);
        Shader shader_vert(string("Shaders/2d_dummy.vert"), string("main"), dev);
        RenderPass render_pass(dev);
        Pipeline pipeline(dev);
        CommandBuffers cmd_buffers(dev);

        list<PhysicalDevice *> devs = engine.getListPhysicalDevices();
        for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
        {
            cout << (*i)->getDeviceName() << endl;
            cout << "0x" << hex << (*i)->getVendorId() << endl;
            cout << "0x" << hex << (*i)->getDeviceId() << endl;
            cout << Version::versionToString((*i)->getApiVersion()) << endl;
            cout << Version::versionToString((*i)->getDriverVersion()) << endl;
        }

        render_pass.initRenderPass(&swap_chain);

        pipeline.setVertexInput();
        pipeline.setInputAssembler();
        pipeline.setVertexShader(&shader_vert);
        pipeline.setFragmentShader(&shader_frag);

        pipeline.setViewPort(window->getWidth(), window->getHeight());
        pipeline.setScissor(swap_chain.getExtent());
        pipeline.createViewportStateInfos();

        pipeline.setRasterizerInfos();
        pipeline.setMultisamplingInfos();
        pipeline.setColorBlendAttachment();
        pipeline.createDynamicStateInfos();
        pipeline.createPipelineLayout();
        pipeline.createPipeline(&render_pass);

        pipeline.initFramebuffers(&swap_chain, &render_pass);

        cmd_buffers.createCommandPool(phys_dev);
        cmd_buffers.createCommandBuffers(pipeline.getFramebuffers());
        cmd_buffers.startRecording(pipeline.getFramebuffers(), &swap_chain, &render_pass, &pipeline);

        while (!window->shouldClose())
        {
            glfwPollEvents();
            cmd_buffers.draw(&swap_chain);
        }

        dev->waitIdle();

        delete window;
        glfwTerminate();
    }
}
