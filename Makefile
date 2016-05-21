SRC =	main.cpp\
		src/model/Building.cpp\
		src/model/Map.cpp\
		src/uiclass/MainWindow.cpp\
		src/utilities/Poller/EventPoller.cpp\
		src/utilities/Poller/Observer.cpp\
		src/utilities/Poller/SDLPoller.cpp

OBJ = $(SRC:%.cpp=%.o)

NAME = feedthesupremleader

CXX = g++
CXXFLAGS = -W -Wall -Werror `sdl2-config --cflags` -Iinclude

LDFLAGS = `sdl2-config --libs`

RM = rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all