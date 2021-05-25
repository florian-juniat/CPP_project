##
## EPITECH PROJECT, 2018
## MAKEFILE
## File description:
## compile makefile
##

NAME	=	server

SRC	=	src/main.cpp	\
		src/client.cpp	\
		src/action.cpp	\
		src/tab_action.cpp	\
		src/party.cpp	\
		src/tab_client.cpp	\
		src/handle.cpp	\
		src/tab_party.cpp	\
		src/data.cpp	\
		src/Enemy.cpp	\
		src/Engine.cpp	\
		src/Player.cpp	\
		src/Lazer_player.cpp	\
		src/Lazer_enemy.cpp	\
		src/Input.cpp	\
		src/Colision.cpp	\
		src/Update.cpp	\
		src/Draw.cpp	\
		src/send_file.cpp	\
		src/Obstacle.cpp


CXXFLAGS	=	-I./include -pthread

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(NAME) -lboost_system -lboost_thread -pthread -lsfml-graphics -lsfml-window -lsfml-system

clean :
	rm -f $(OBJ)
	rm -f *~

fclean : clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
