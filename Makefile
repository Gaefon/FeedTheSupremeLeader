SRC =	main.cpp\
		src/menu.cpp\
		src/parameters.cpp\
		src/game.cpp\
		src/model/Building.cpp\
		src/helper/RectHelper.cpp\
		src/helper/ColorHelper.cpp\
		src/model/Map.cpp\
		src/uiclass/MainWindow.cpp\
		src/uiclass/Button.cpp\
		src/utilities/Poller/EventPoller.cpp\
		src/utilities/Poller/Observer.cpp\
		src/utilities/Poller/SDLPoller.cpp\
		src/utilities/Config.cpp\
		src/utilities/sounds/sounds.cpp

OBJ =	$(SRC:%.cpp=%.o)


NAME =	feedthesupremleader

CXX = g++
CXXFLAGS = -W -Wall -std=c++11 `sdl2-config --cflags` -Iinclude

LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

RM = rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
