##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile games
##

SRC	=	src/accept_request_one.c \
		src/add_clients.c \
		src/broadcast_mngt.c \
		src/channel_mngt.c \
		src/check_exists.c \
		src/command_mngt.c \
		src/comment_mngt.c \
		src/connection_mngt.c \
		src/error_handling_s.c \
		src/finders.c \
		src/getters.c \
		src/helpers.c \
		src/load_chan.c \
		src/load_comment.c \
		src/load_session.c \
		src/load_thread.c \
		src/load_user.c \
		src/login.c \
		src/logout.c \
		src/main.c \
		src/response_mngt.c \
		src/save_session.c \
		src/save_user.c \
		src/session_config.c \
		src/str_to_word_array.c \
		src/subscribe_mngt.c \
		src/team_mngt.c \
		src/thread_mngt.c \
		src/use_resources.c \
		src/use_thread.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	myteams_server

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
