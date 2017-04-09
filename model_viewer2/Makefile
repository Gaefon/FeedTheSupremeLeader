#SRC =	main.cpp\
#		src/Shader.cpp\
#		src/Camera.cpp\
#		src/Model.cpp\
#		src/Scene.cpp\
#		src/Texture.cpp\
#		src/SDLTexture.cpp\
#		src/Light.cpp\
#		src/helper/DebugHelper.cpp

SRC =	src/GEngine.cpp\
		src/Const.cpp\
		src/PhysicalDevice.cpp\
		src/Version.cpp\
		src/Surface.cpp\
		src/Device.cpp\
		src/Window.cpp\
		src/SwapChain.cpp\
		src/ImageView.cpp\
		src/Shader.cpp\
		src/Pipeline.cpp\
		src/RenderPass.cpp\
		src/Framebuffers.cpp\
		src/CommandBuffers.cpp\
		src/Semaphore.cpp\
		src/bitmaps/Bitmap.cpp\
		src/pool/PipelinePool.cpp\
		src/GEngineWrapper.cpp\
		main2.cpp

VERT =	Shaders/2d_dummy.vert

FRAG =	Shaders/2d_dummy.frag

GLSLVCONF =	glslvalid.conf

OBJ =		$(SRC:.cpp=.o)
SPV_VERT =	$(VERT:.vert=.vert.spv)
SPV_FRAG =	$(FRAG:.frag=.frag.spv)

NAME =	modelviewer

CXX = g++
GLSLVALIDATOR = glslangValidator
CXXFLAGS = -W -Wall -std=c++11 -Iinclude `pkg-config --cflags glfw3` -g

LDFLAGS = `pkg-config --libs glfw3` -lvulkan

RM = rm -rf



all:		$(NAME) shaders

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)


shaders:	$(SPV_VERT) $(SPV_FRAG)

%.vert.spv:	%.vert
			$(GLSLVALIDATOR) -V $< -o $@

%.frag.spv:	%.frag
			$(GLSLVALIDATOR) -V $< -o $@
			

clean:
			$(RM) $(OBJ)
			$(RM) $(SPV_VERT)
			$(RM) $(SPV_FRAG)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: clean fclean re all shaders
