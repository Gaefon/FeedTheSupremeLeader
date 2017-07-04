#include <GEngineWrapper.h>
#include <Window.h>
#include <events/KeyboardPoller.h>
#include <events/MousePoller.h>
#include <Shader.h>
#include <pool/PipelinePool.h>
#include <Camera.h>

#include <models/Scene.h>
#include <models/Model.h>

#include <string>

using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	KeyboardPoller *key_event;
	MousePoller *mouse_event;
	list<string> extensions;
	
	std::vector<VertexBufferData> vertices;
	std::vector<uint16_t> indexes;
	

	glfwInit();

	window = new Window("Heroes never die !", 800, 600);
	key_event = new KeyboardPoller(window);
	mouse_event = new MousePoller(window);

	GEngineWrapper g_engine_wrapper(window);
	
	// create the pipeline
	Shader *shader_frag = new Shader(string("Shaders/2d_dummy.frag"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	Shader *shader_vert = new Shader(string("Shaders/2d_dummy.vert"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	PipelinePool::getInstance()->createPipeline(0, shader_vert, shader_frag, &g_engine_wrapper);
	
	glm::vec3 cam_pos(2.0f, 2.0f, 2.0f);
	glm::vec3 cam_target(0.0f, 0.0f, 0.0f);
	glm::vec3 cam_vert(0.0f, 0.0f, 1.0f);
	Camera camera;
	camera.setPerspectice(90.0f, (float) window->getWidth() / (float) window->getHeight(), 0.1f, 100.0f);
	camera.setLookAt(cam_pos, cam_target, cam_vert);
	
	vertices =
        {
			{{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
			{{0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
			{{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}
		};
   indexes = {0, 1, 2, 3, 4, 0, 3, 5, 6, 5, 2, 7};
	
	//g_engine_wrapper.startRecording(PipelinePool::getInstance()->getPipeline(0), vertices, indexes);
	
	Scene scene;
	Material mat(PipelinePool::getInstance()->getPipeline(0));
	Model model1;
	Model model2;
	
	
	model1.addVertice(new Vertex({0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}));
	model1.addVertice(new Vertex({-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	model1.addVertice(new Vertex({-0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));
	model1.addVertice(new Vertex({0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));
	model1.addVertice(new Vertex({0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	model1.addVertice(new Vertex({0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}));
	model1.addVertice(new Vertex({0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	model1.addVertice(new Vertex({-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	
	model1.addIndex(0);
	model1.addIndex(1);
	model1.addIndex(2);
	model1.addIndex(3);
	model1.addIndex(4);
	model1.addIndex(0);
	model1.addIndex(3);
	model1.addIndex(5);
	model1.addIndex(6);
	model1.addIndex(5);
	model1.addIndex(2);
	model1.addIndex(7);
	
	model1.setMaterial(&mat);
	
	/*model1.addVertice(new Vertex({0.0f, 0.5f}, {1.0f, 0.0f, 0.0f});
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
	model2.addVertice(new Vertex({-0.5f, -0.5f}, {0.0f, 1.0f, 0.0f});*/
	
	scene.addModel(&model1);
	//scene.addModel(&model2);
	
	scene.render(&g_engine_wrapper);

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
