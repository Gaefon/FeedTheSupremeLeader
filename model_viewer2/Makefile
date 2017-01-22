SRC =	src/main.cpp\
		src/Shader.cpp\
		src/Camera.cpp\
		src/Model.cpp\
		src/Scene.cpp\
		src/Texture.cpp\
		src/SDLTexture.cpp\
		src/Light.cpp

OBJ =	$(SRC:%.cpp=%.o)


NAME =	modelviewer

CXX = g++
CXXFLAGS = -W -Wall -std=c++11 `sdl2-config --cflags` -lGL -lGLEW -Iinclude

LDFLAGS = `sdl2-config --libs` -lGL -lGLEW

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
