##
## EPITECH PROJECT, 2018
## MAKEFILE
## File description:
## compile makefile
##

NAME	=	audio_test

SRC	=	audio.cpp\
		testAudio.cpp\

CXXFLAGS	=	-I./inc -g

LIB	=	libportaudio.a

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(CXXFLAGS) -o $(NAME) $(OBJ) $(LIB) -lrt -lm -lasound -ljack -pthread -lopus

clean :
	rm -f $(OBJ)
	rm -f *~

fclean : clean
	rm -rf $(NAME)

re:	fclean all

