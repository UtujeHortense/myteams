/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server erroh handling
*/

#include "server.h"

void exit_with_error(char *errmsg)
{
    printf("%s\n", errmsg);
    exit(84);
}

void command_check(char *cmd)
{
    cmd[strlen(cmd) - 2] = '\0';
}

int error_handling_server(int ac, char **av)
{
    (void)av;
    if (ac != 2)
        exit(84);
    if (strcmp(av[1], "-help") == 0) {
        printf("%s\n\n", "USAGE: ./myteams_server port");
        printf("%s", "       port   is the port ");
        printf("%s\n", "number on which the server socket listens");
        exit(0);
    }
    return 0;
}