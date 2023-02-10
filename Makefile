##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile MYTEAMS
## 


SERVERDIR	=	./server

CLIENTDIR	=	./client

all:	client server

server:
	$(MAKE) -C$(SERVERDIR)

client:
	$(MAKE)	-C$(CLIENTDIR)

clean:
	rm -f *~
	$(MAKE)	-C$(SERVERDIR) clean
	$(MAKE)	-C$(CLIENTDIR) clean


fclean:	clean
	$(MAKE)	-C$(SERVERDIR) fclean
	$(MAKE)	-C$(CLIENTDIR) fclean

re:	fclean all

.PHONY:	all client server clean fclean re