SRC =	main.cpp\
		Shader.cpp\
		Camera.cpp\
		Model.cpp\
		Scene.cpp

OBJ =	$(SRC:%.cpp=%.o)


NAME =	modelviewer

CXX = g++
CXXFLAGS = -W -Wall -std=c++11 `sdl2-config --cflags` -lGL -lGLEW

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
