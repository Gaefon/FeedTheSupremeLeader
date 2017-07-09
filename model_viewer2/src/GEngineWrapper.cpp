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
        delete g_index_buffer;
        delete g_staging_buffer2;
        delete g_vertex_buffer;
        delete g_staging_buffer;
        PipelinePool::getInstance()->destroyAllThePipelines();
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

    void GEngineWrapper::initRenderPass()
    {
        g_render_pass = new RenderPass(g_engine->getLogicalDevice());
        g_render_pass->initRenderPass(g_swapchain);

    }

    void GEngineWrapper::initCmdBuffers()
    {
        g_command_buffers = new CommandBuffers(g_engine->getLogicalDevice());
    }
    
    void GEngineWrapper::beginCommandBufferAndRenderPass(Framebuffers *framebuffers)
    {
		g_command_buffers->createCommandPool(g_physical_device);
		g_command_buffers->createCommandBuffers(framebuffers);
		g_command_buffers->beginCommandBufferAndRenderPass(g_render_pass, framebuffers, g_swapchain);
    }
    
    // passer les vertices et les index en arguments depuis l'objet Scene
	void GEngineWrapper::startRecording(Pipeline *pipeline, vector<VertexBufferData> vertices, vector<uint16_t> indexes)
    {
		g_staging_buffer = new StagingBuffer(g_engine->getLogicalDevice());

		g_staging_buffer->createBuffer(sizeof(VertexBufferData) * vertices.size());
		g_staging_buffer->allocBuffer();
		g_staging_buffer->bindToDevice();
		g_staging_buffer->addVertexData(&vertices);

		//creation vertex buffers
		g_vertex_buffer = new VertexBuffer(g_engine->getLogicalDevice());
		g_vertex_buffer->createBuffer(sizeof(VertexBufferData) * vertices.size());
		g_vertex_buffer->allocBuffer();
		g_vertex_buffer->bindToDevice();
		g_vertex_buffer->setNbVertices(g_staging_buffer->getNbVertices());

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

		g_command_buffers->copyBufferCommand(g_staging_buffer->getVulkanBuffer(), g_vertex_buffer->getVulkanBuffer(), sizeof(VertexBufferData) * vertices.size());
		g_command_buffers->copyBufferCommand(g_staging_buffer2->getVulkanBuffer(), g_index_buffer->getVulkanBuffer(), sizeof(uint16_t) * indexes.size());
		
		g_command_buffers->startRecording(pipeline, g_vertex_buffer, g_index_buffer);
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

    void GEngineWrapper::startDrawing()
    {
        g_command_buffers->draw(g_swapchain);
    }
}
