##
## EPITECH PROJECT, 2018
## MAKEFILE
## File description:
## compile makefile
##

NAME	=	serveur

SRC	=	src/main.cpp	\
		src/serveur.cpp	\
		src/communicate.cpp	\
		src/contact.cpp	\
		src/list_connect.cpp

CXXFLAGS	=	-I./include -pthread

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(NAME) -lboost_system -lboost_thread

clean :
	rm -f $(OBJ)
	rm -f *~

fclean : clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
