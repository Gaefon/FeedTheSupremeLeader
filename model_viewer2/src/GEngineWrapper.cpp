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
        delete g_vertex_buffer;
        delete g_staging_buffer;
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

        vertices =
        {
			{{0.0f, 0.5f}, {1.0f, 0.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
			{{0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}
		};
       indexes = {0,1,2,3,4,0,3,5,6,5,2,7};

       createPipeline();
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
        g_staging_buffer = new StagingBuffer(g_engine->getLogicalDevice());


        g_staging_buffer->createBuffer(sizeof(Vertex) * vertices.size());
        g_staging_buffer->allocBuffer();
        g_staging_buffer->bindToDevice();
        g_staging_buffer->addVertexData(&vertices);


        //creation vertex buffers
		g_vertex_buffer = new VertexBuffer(g_engine->getLogicalDevice());
		g_vertex_buffer->createBuffer(sizeof(Vertex) * vertices.size());
		g_vertex_buffer->allocBuffer();
        g_vertex_buffer->bindToDevice();


        g_staging_buffer2 = new StagingBuffer(g_engine->getLogicalDevice());
        g_staging_buffer2->createBuffer(sizeof(uint16_t) * indexes.size());
        g_staging_buffer2->allocBuffer();
        g_staging_buffer2->bindToDevice();
        g_staging_buffer2->addVertexData(&indexes);
        
        g_index_buffer = new IndexBuffer(g_engine->getLogicalDevice());
        g_index_buffer->createBuffer(sizeof(uint16_t) * indexes.size());
        g_index_buffer->allocBuffer();
        g_index_buffer->bindToDevice();
        g_index_buffer->setNbVertices(g_staging_buffer2->getNbVertices());
        
        g_command_buffers->createCommandBuffers(g_pipeline->getFramebuffers());
        g_command_buffers->copyBufferCommand(g_staging_buffer->getVulkanBuffer(), g_vertex_buffer->getVulkanBuffer(), sizeof(Vertex) * vertices.size());
        g_command_buffers->copyBufferCommand(g_staging_buffer2->getVulkanBuffer(), g_index_buffer->getVulkanBuffer(), sizeof(uint16_t) * indexes.size());
        g_vertex_buffer->setNbVertices(g_staging_buffer->getNbVertices());
        g_command_buffers->startRecording(g_pipeline->getFramebuffers(), g_swapchain, g_render_pass, g_pipeline, g_vertex_buffer, g_index_buffer);


    }

    Engine *GEngineWrapper::getEngine()
    {
        return g_engine;
    }
    
    Window *GEngineWrapper::getWindow()
    {
    	return g_window;
    }
    
    SwapChain *GEngineWrapper::getSwapchain()
    {
    	return g_swapchain;
    }
    
    RenderPass *GEngineWrapper::getRenderPass()
    {
    	return g_render_pass;
    }

    void GEngineWrapper::startDrawing()
    {
        g_command_buffers->draw(g_swapchain);
    }
}
