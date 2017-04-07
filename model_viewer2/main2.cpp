#include <GEngine.h>
#include <Version.h>
#include <Window.h>
#include <Surface.h>
#include <Device.h>
#include <SwapChain.h>
#include <Shader.h>
#include <Framebuffers.h>
#include <Pipeline.h>
#include <CommandBuffers.h>
#include <Semaphore.h>


#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <string>

using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	list<string> extensions;

	glfwInit();

	window = new Window("kek", 800, 600);


	Engine engine;
	engine.enableValidationLayers();
	engine.init("test", Version::makeVersion(1, 0, 0));
	engine.addExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	engine.pickPhysicalDevices();


	Surface surface(&engine, window);
	PhysicalDevice *phys_dev = surface.getSuitableDevice(&engine);
	Device dev(phys_dev, engine.getExtensions());
	SwapChain swap_chain(&surface, window, phys_dev, &dev);
	Shader shader_frag(string("Shaders/2d_dummy.frag"), string("main"), &dev);
	Shader shader_vert(string("Shaders/2d_dummy.vert"), string("main"), &dev);
	RenderPass render_pass;
	Pipeline pipeline;
	Framebuffers framebuffers;
	CommandBuffers cmd_buffers;
	Semaphore image_available;
	Semaphore render_finished;


	list<PhysicalDevice *> devs = engine.getListPhysicalDevices();
	for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
	{
		cout << (*i)->getDeviceName() << endl;
		cout << "0x" << hex << (*i)->getVendorId() << endl;
		cout << "0x" << hex << (*i)->getDeviceId() << endl;
		cout << Version::versionToString((*i)->getApiVersion()) << endl;
		cout << Version::versionToString((*i)->getDriverVersion()) << endl;
	}

	render_pass.initRenderPass(&swap_chain, &dev);

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
	pipeline.createPipelineLayout(&dev);
	pipeline.createPipeline(&render_pass);

	framebuffers.createFramebuffer(&dev, &swap_chain, &render_pass);

	cmd_buffers.createCommandPool(&dev, phys_dev);
	cmd_buffers.createCommandBuffers(&framebuffers);
	cmd_buffers.startRecording(&framebuffers, &swap_chain, &render_pass, &pipeline);
	
	image_available.createSemaphore(&dev);
	render_finished.createSemaphore(&dev);

	while (!window->shouldClose())
	{
		glfwPollEvents();
		cmd_buffers.draw(&swap_chain, &image_available, &render_finished);
	}
	
	dev.waitIdle();

	delete window;
	glfwTerminate();

	return 0;
}
