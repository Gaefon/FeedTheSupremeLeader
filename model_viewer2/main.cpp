#include <GEngineWrapper.h>
#include <Window.h>
#include <events/KeyboardPoller.h>
#include <events/MousePoller.h>
#include <Shader.h>
#include <pool/PipelinePool.h>
#include <Camera.h>
#include <Sampler.h>

#include <models/Scene.h>
#include <models/Model.h>
#include <models/Texture.h>

#include <bitmaps/BMPImage.h>

#include <string>

#include <unistd.h>
#include <math.h>

using namespace GEngine;
using namespace std;

int main(void)
{
	Window *window;
	KeyboardPoller *key_event;
	MousePoller *mouse_event;
	list<string> extensions;

	// std::vector<VertexBufferData> vertices;
	// std::vector<uint16_t> indexes;


	glfwInit();

	window = new Window("Heroes never die !", 800, 600);
	key_event = new KeyboardPoller(window);
	mouse_event = new MousePoller(window);

	GEngineWrapper g_engine_wrapper(window);

	// create the pipeline
	Shader *shader_frag = new Shader(string("Shaders/2d_dummy.frag"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	Shader *shader_vert = new Shader(string("Shaders/2d_dummy.vert"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	Shader *stupid_frag = new Shader(string("Shaders/2d_stupid.frag"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());
	Shader *stupid_vert = new Shader(string("Shaders/2d_stupid.vert"), string("main"), g_engine_wrapper.getEngine()->getLogicalDevice());

	PipelinePool::getInstance()->createPipeline(0, shader_vert, shader_frag, &g_engine_wrapper);
	PipelinePool::getInstance()->createPipeline(1, stupid_vert, stupid_frag, &g_engine_wrapper);

	glm::vec3 cam_pos(2.0f, 2.0f, 2.0f);
	glm::vec3 cam_target(0.0f, 0.0f, 0.0f);
	glm::vec3 cam_vert(0.0f, 0.0f, 1.0f);
	Camera camera;
	camera.setPerspective(90.0f, (float) window->getWidth() / (float) window->getHeight(), 0.1f, 100.0f);
	camera.setLookAt(cam_pos, cam_target, cam_vert);

	//g_engine_wrapper.startRecording(PipelinePool::getInstance()->getPipeline(0), vertices, indexes);

	BMPImage plop("../ressources/test.bmp");
	//BMPImage plop("../ressources/fuckdatshit_bad_number_bytes_per_lines.bmp");


	Scene scene;
	Material mat1(PipelinePool::getInstance()->getPipeline(0));
	Material mat2(PipelinePool::getInstance()->getPipeline(1));
	Sampler sampler(g_engine_wrapper.getEngine()->getLogicalDevice());
	Texture tex(g_engine_wrapper.getEngine()->getLogicalDevice(), &plop);
	tex.setSampler(&sampler);

	Model model1;
	Model model2;

	model1.addVertice(new Vertex({0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}));
	model1.addVertice(new Vertex({-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	model1.addVertice(new Vertex({-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));
	model1.addVertice(new Vertex({1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));
	model1.addVertice(new Vertex({1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}));

	model1.addIndex(0);
	model1.addIndex(1);
	model1.addIndex(2);
	model1.addIndex(0);
	model1.addIndex(3);
	model1.addIndex(4);

	model1.setMaterial(&mat1);

	model2.addVertice(new Vertex({0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}));
	model2.addVertice(new Vertex({-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));
	model2.addVertice(new Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	model2.addVertice(new Vertex({1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}));
	model2.addVertice(new Vertex({1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));

	model2.addIndex(0);
	model2.addIndex(1);
	model2.addIndex(2);
	model2.addIndex(0);
	model2.addIndex(3);
	model2.addIndex(4);

	model2.setMaterial(&mat2);

	Model cube;

	cube.addVertice(new Vertex({-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.6666f}));
	cube.addVertice(new Vertex({-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.75f, 0.6666f}));
	cube.addVertice(new Vertex({0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.75f, 0.3333f}));
	cube.addVertice(new Vertex({0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.3333f}));

	cube.addVertice(new Vertex({-0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.25f, 0.6666f}));
	cube.addVertice(new Vertex({-0.5f, 0.5f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.5f, 0.6666f}));
	cube.addVertice(new Vertex({0.5f, 0.5f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.5f, 0.3333f}));
	cube.addVertice(new Vertex({0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.25f, 0.3333f}));

	cube.addVertice(new Vertex({-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.6666f}));
	cube.addVertice(new Vertex({0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.3333f}));

	cube.addVertice(new Vertex({0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.25f, 0.0f}));
	cube.addVertice(new Vertex({0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.5f, 0.0f}));

	cube.addVertice(new Vertex({-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.5f, 1.0f}));
	cube.addVertice(new Vertex({-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.25f, 1.0f}));


	cube.addIndex(0);
	cube.addIndex(1);
	cube.addIndex(2);
	cube.addIndex(2);
	cube.addIndex(3);
	cube.addIndex(0);

	cube.addIndex(5);
	cube.addIndex(4);
	cube.addIndex(6);
	cube.addIndex(6);
	cube.addIndex(4);
	cube.addIndex(7);

	cube.addIndex(6);
	cube.addIndex(1);
	cube.addIndex(5);
	cube.addIndex(6);
	cube.addIndex(2);
	cube.addIndex(1);

	cube.addIndex(4);
	cube.addIndex(8);
	cube.addIndex(7);
	cube.addIndex(7);
	cube.addIndex(8);
	cube.addIndex(9);

	cube.addIndex(6);
	cube.addIndex(7);
	cube.addIndex(11);
	cube.addIndex(11);
	cube.addIndex(7);
	cube.addIndex(10);

	cube.addIndex(4);
	cube.addIndex(5);
	cube.addIndex(13);
	cube.addIndex(5);
	cube.addIndex(12);
	cube.addIndex(13);

	cube.setMaterial(&mat1);
	cube.setTexture(&tex);

	//scene.addModel(&model1);
	//scene.addModel(&model2);
	scene.addModel(&cube);


	scene.render(&g_engine_wrapper, &camera);
	int angle = 0;
	while (!window->shouldClose())
	{
		key_event->poll();

		for (KeyEvent *evt: key_event->getEvents())
			cout << (int) evt->getKey() << " " << evt->isPressed() << endl;

		for (MouseEvent *evt : mouse_event->getEvents())
		{
			/*if (evt->getType() == MouseEvent::Type::position)
				cout << "X = " << evt->getPosX() << " // Y = " << evt->getPosY() << endl;
			else if (evt->getType() == MouseEvent::Type::scroll)
				cout << "SCROLL :: X = " << evt->getOffsetX() << " // Y = " << evt->getOffsetY() << endl;
			else
				cout << "Button = " << (int) evt->getType() << " // pressed = " << evt->isPressed() << endl;*/
		}
		mouse_event->poll();

		cam_pos.x = 2.0 * cos(2 * M_PI * angle / 360.0f);
		cam_pos.y = 2.0 * sin(2 * M_PI * angle / 360.0f);
		camera.setLookAt(cam_pos, cam_target, cam_vert);
		angle = (angle + 1) % 360;
		scene.render(&g_engine_wrapper, &camera);
		g_engine_wrapper.startDrawing();
		usleep(20000);

	}

	g_engine_wrapper.getEngine()->getLogicalDevice()->waitIdle();

	//delete shader_frag;
	//delete shader_vert;
	//delete stupid_frag;
	//delete stupid_vert;

	delete key_event;
	delete window;
	glfwTerminate();

	return 0;
}
