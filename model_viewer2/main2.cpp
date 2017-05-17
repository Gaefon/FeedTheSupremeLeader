#include <GEngineWrapper.h>
#include <Window.h>
#include <events/KeyboardPoller.h>
#include <events/MousePoller.h>
#include <Shader.h>
#include <pool/PipelinePool.h>

//#include <model/Scene.h>
//#include <model/Model.h>

#include <string>

using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	KeyboardPoller *key_event;
	MousePoller *mouse_event;
	list<string> extensions;
	

	glfwInit();

	window = new Window("Heroes never die !", 800, 600);
	key_event = new KeyboardPoller(window);
	mouse_event = new MousePoller(window);

	GEngineWrapper g_engine_wrapper(window);
	
	// create the pipeline
	Shader *shader_frag = new Shader(string("Shaders/2d_dummy.frag"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	Shader *shader_vert = new Shader(string("Shaders/2d_dummy.vert"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	PipelinePool::getInstance()->createPipeline(0, shader_vert, shader_frag, &g_engine_wrapper);
	
	g_engine_wrapper.startRecording(PipelinePool::getInstance()->getPipeline(0));
	/*Scene scene;
	Model model1;
	Model model2;
	
	model1.addVertice(new Vertex({0.0f, 0.5f}, {1.0f, 0.0f, 0.0f});
	model1.addVertice(new Vertex({-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f});
	model1.addVertice(new Vertex({-0.5f, 0.0f}, {0.0f, 0.0f, 1.0f});

	model1.addVertice(new Vertex({0.0f, 0.5f}, {1.0f, 0.0f, 0.0f});
	model1.addVertice(new Vertex({0.5f, 0.0f}, {0.0f, 0.0f, 1.0f});
	model1.addVertice(new Vertex({0.5f, 0.5f}, {0.0f, 1.0f, 0.0f});
	
	
	
	model2.addVertice(new Vertex({0.5f, 0.0f}, {0.0f, 0.0f, 1.0f});
	model2.addVertice(new Vertex({0.0f, -0.5f}, {1.0f, 0.0f, 0.0f});
	model2.addVertice(new Vertex({0.5f, -0.5f}, {0.0f, 1.0f, 0.0f});
	
	model2.addVertice(new Vertex({0.0f, -0.5f}, {1.0f, 0.0f, 0.0f});
	model2.addVertice(new Vertex({-0.5f, 0.0f}, {0.0f, 0.0f, 1.0f});
	model2.addVertice(new Vertex({-0.5f, -0.5f}, {0.0f, 1.0f, 0.0f});
	
	scene.addModel(&model1);
	scene.addModel(&model2);
	
	scene.render(&g_engine_wrapper);*/

	while (!window->shouldClose())
	{
		key_event->poll();
		
		for (KeyEvent *evt: key_event->getEvents())
			cout << (int) evt->getKey() << " " << evt->isPressed() << endl;
			
		for (MouseEvent *evt : mouse_event->getEvents())
		{
			if (evt->getType() == MouseEvent::Type::position)
				cout << "X = " << evt->getPosX() << " // Y = " << evt->getPosY() << endl;
			else if (evt->getType() == MouseEvent::Type::scroll)
				cout << "SCROLL :: X = " << evt->getOffsetX() << " // Y = " << evt->getOffsetY() << endl;
			else
				cout << "Button = " << (int) evt->getType() << " // pressed = " << evt->isPressed() << endl;
		}
		mouse_event->poll();
		
		g_engine_wrapper.startDrawing();
	}
	
	g_engine_wrapper.getEngine()->getLogicalDevice()->waitIdle();

	delete key_event;
	delete window;
	glfwTerminate();

	return 0;
}
