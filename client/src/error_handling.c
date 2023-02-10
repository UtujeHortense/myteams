/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** client erroh handling
*/

#include "client.h"

void usage(bool error)
{
    if (error) {
        printf("Error\n");
        exit(84);
    }
    else {
        printf("USAGE: ./myteams_cli ip port\n\tip\tis");
        printf(" the server ip address on which the server");
        printf(" socket listens\n\tport\tis the port number");
        printf(" on which the server socket listens\n");
    }
    exit(0);
}

bool is_numbers(char *string)
{
    for (size_t i = 0; i < strlen(string); i++) {
        if ((string[i] >= '0' && string[i] <= '9') || string[i] == '.')
            continue;
        return false;
    }
    return true;
}

bool command_is_valid(char **args)
{
    if (args == NULL) {
        return true;
    }
    else if (strcmp(args[0], "err") == 0) {
        return false;
    }
    return true;
}

void error_handling_client(int ac, char **av)
{
    if ((ac == 2) && strcmp(av[1], "-help") == 0)
        usage(false);
    else if (ac != 3)
        usage(true);
    else if (!is_numbers(av[2]))
        usage(true);
}