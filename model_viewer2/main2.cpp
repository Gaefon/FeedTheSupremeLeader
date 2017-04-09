#include <GEngine.h>
#include <Version.h>
#include <Window.h>
#include <Surface.h>
#include <SwapChain.h>
#include <Shader.h>
#include <Pipeline.h>
#include <CommandBuffers.h>

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

	// mettre la creation de surface et device vituelle dans la classe Engine (?)
	Surface surface(&engine, window);
	PhysicalDevice *phys_dev = surface.getSuitableDevice(&engine);
	engine.createLogicalDevice(phys_dev);
	Device *dev = engine.getLogicalDevice();
	

	SwapChain swap_chain(&surface, window, phys_dev, dev);
	Shader shader_frag(string("Shaders/2d_dummy.frag"), string("main"), dev);
	Shader shader_vert(string("Shaders/2d_dummy.vert"), string("main"), dev);
	RenderPass render_pass;
	Pipeline pipeline(dev);
	CommandBuffers cmd_buffers;

	list<PhysicalDevice *> devs = engine.getListPhysicalDevices();
	for (list<PhysicalDevice *>::iterator i = devs.begin(); i != devs.end(); i++)
	{
		cout << (*i)->getDeviceName() << endl;
		cout << "0x" << hex << (*i)->getVendorId() << endl;
		cout << "0x" << hex << (*i)->getDeviceId() << endl;
		cout << Version::versionToString((*i)->getApiVersion()) << endl;
		cout << Version::versionToString((*i)->getDriverVersion()) << endl;
	}

	render_pass.initRenderPass(&swap_chain, dev);

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

	cmd_buffers.createCommandPool(dev, phys_dev);
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

	return 0;
}
