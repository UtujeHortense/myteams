##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile games
##


SRC	=	src/main.c \
		src/error_handling.c \
		src/communication.c 	\
		src/command_parser.c 	\
		src/helpers.c 	\
		src/login_cli.c 	\
		src/logout_cli.c \
		src/help.c \
		src/create_all.c \
		src/use_all.c \
		src/create_channel.c \
		src/use_channel.c \
		src/create_thread.c \
		src/buffer_mngt.c \
		src/free_alloc.c \
		src/response_one.c \
		src/reply_analysis.c \
		src/size_mngt.c \
		src/response_two.c \
		src/use_thread.c \
		src/send_request_one.c \
		src/str_to_array.c \
		src/create_comment.c \
		src/subscribe_to_team.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	myteams_cli

CFLAGS	+=	 -Wall -Wextra -I./include -g 

LDFLAGS +=	 -L../libs/myteams -ldl -luuid -lmyteams

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
	mv $(NAME) ../

clean:
	rm -f *~
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all
