SRC =	main.cpp\
		src/menu.cpp\
		src/parameters.cpp\
		src/game.cpp\
		src/helper/RectHelper.cpp\
		src/helper/ColorHelper.cpp\
		src/model/Map.cpp\
		src/model/Building.cpp\
		src/model/Farm.cpp\
		src/model/House.cpp\
		src/model/School.cpp\
		src/model/Road.cpp\
		src/uiclass/Widget.cpp\
		src/uiclass/MainWindow.cpp\
		src/uiclass/Button.cpp\
		src/uiclass/Label.cpp\
		src/uiclass/GameMenuDialog.cpp\
		src/uiclass/GameInterface.cpp\
		src/uiclass/Minimap.cpp\
		src/uiclass/Slider.cpp\
		src/uiclass/Commissar.cpp\
		src/utilities/Poller/SDLPoller.cpp\
		src/utilities/Poller/MapPoller.cpp\
		src/utilities/Config.cpp\
		src/utilities/RessourceManager.cpp\
		src/utilities/BuildingHelper.cpp\
		src/utilities/Timer.cpp\
		src/utilities/sounds/sounds.cpp\
		src/lib/jsonCpp/jsoncpp.cpp\
		src/model/Village.cpp

OBJ =	$(SRC:%.cpp=%.o)


NAME =	feedthesupremleader

CXX = g++
CXXFLAGS = -W -Wall -Werror -std=c++11 `sdl2-config --cflags` -Iinclude

LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lSDL2_mixer -lm

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
