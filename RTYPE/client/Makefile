##
## EPITECH PROJECT, 2018
## MAKEFILE
## File description:
## compile makefile
##

NAME	=	client

SRC	=	src/main.cpp	\
		src/handle.cpp	\
		src/data.cpp

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
