##
## EPITECH PROJECT, 2018
## MAKEFILE
## File description:
## compile makefile
##

NAME	=	client

SRC	=	src/main.cpp	\
		src/audio.cpp

CXXFLAGS	=	-I./include -pthread

LIB	=	libportaudio.a

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o $(NAME) $(LIB) -lboost_system -lboost_thread -lrt -lm -lasound -ljack -pthread -lopus

clean :
	rm -f $(OBJ)
	rm -f *~

fclean : clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
