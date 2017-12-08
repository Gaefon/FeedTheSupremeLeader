#include <GEngineWrapper.h>

#include <pool/PipelinePool.h>

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
        delete g_command_pool;
        /*delete g_index_buffer;
        delete g_staging_buffer2;
        delete g_vertex_buffer;
        delete g_staging_buffer;*/
        PipelinePool::getInstance()->destroyAllThePipelines();
        delete g_framebuffers;
        delete g_render_pass;
		delete g_depth_test;
        delete g_swapchain;
        delete g_surface;
        delete g_engine;
    }

    void GEngineWrapper::init()
    {
		initEngine("test");
		initDevices();
		initSwapChain();
		initCmdPool();
		initDepthTest();
		initRenderPass();
		initFrameBuffers();
		initCmdBuffers();
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
    
	void GEngineWrapper::initDepthTest()
	{
		g_depth_test = new DepthTest(g_engine->getLogicalDevice());
		g_depth_test->createDepthTest(g_swapchain, g_command_pool);
	}

    void GEngineWrapper::initRenderPass()
    {
        g_render_pass = new RenderPass(g_engine->getLogicalDevice());
        g_render_pass->initRenderPass(g_swapchain, g_depth_test);

    }

    void GEngineWrapper::initFrameBuffers()
    {
    	g_framebuffers = new Framebuffers(g_engine->getLogicalDevice());
		g_framebuffers->createFramebuffer(g_swapchain, g_render_pass, g_depth_test);
    }
    
    void GEngineWrapper::initCmdPool()
    {
    	g_command_pool = new CommandPool(g_engine->getLogicalDevice());
		g_command_pool->createCommandPool();
    }
    
    void GEngineWrapper::initCmdBuffers()
    {
        g_command_buffers = new CommandBuffers(g_engine->getLogicalDevice(), g_command_pool);
    }

    void GEngineWrapper::beginCommandBufferAndRenderPass()
    {
		g_command_buffers->createCommandBuffers(g_framebuffers);
		g_command_buffers->beginCommandBufferAndRenderPass(g_render_pass, g_framebuffers, g_swapchain);
    }

    // passer les vertices et les index en arguments depuis l'objet Scene
	void GEngineWrapper::startRecording(Pipeline *pipeline, vector<VertexBufferData> vertices, vector<uint16_t> indexes, Texture *tex, Camera *camera)
    {
		pipeline->setVerticesAndIndexes(vertices, indexes);
		pipeline->getUniformBuffer()->setMatrix(camera->getModelView(), camera->getProjection());
	    
		pipeline->updateDescriptorSet(tex);
		g_command_buffers->copyBufferCommand(pipeline->getVertexStagingBuffer()->getVulkanBuffer(), pipeline->getVertexBuffer()->getVulkanBuffer(), sizeof(VertexBufferData) * vertices.size());
		g_command_buffers->copyBufferCommand(pipeline->getIndexStagingBuffer()->getVulkanBuffer(), pipeline->getIndexBuffer()->getVulkanBuffer(), sizeof(uint16_t) * indexes.size());
		//g_command_buffers->createCommandBuffers(g_framebuffers);
		
		g_command_buffers->startRecording(pipeline, pipeline->getVertexBuffer(), pipeline->getIndexBuffer());
    }

    void GEngineWrapper::endCommandBufferAndRenderPass()
    {
		g_command_buffers->endCommandBufferAndRenderPass();
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
    
    CommandPool *GEngineWrapper::getCommandPool()
    {
    	return g_command_pool;
    }

    void GEngineWrapper::startDrawing()
    {
		g_command_buffers->draw(g_swapchain);
    }
}
