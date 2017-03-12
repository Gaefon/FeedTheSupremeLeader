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
		main2.cpp

OBJ =	$(SRC:%.cpp=%.o)


NAME =	modelviewer

CXX = g++
CXXFLAGS = -W -Wall -std=c++11 -Iinclude `pkg-config --cflags glfw3`

LDFLAGS = `pkg-config --libs glfw3` -lvulkan

RM = rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: clean fclean re all
