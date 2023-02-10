/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** main function
*/

#include "client.h"

int main(int ac, char **av)
{
    error_handling_client(ac, av);

    int skt = socket(PF_INET, SOCK_STREAM, 0);
    if (!init_connection(skt, av[1], atoi(av[2])) == true)
        printf("==== Error can't connect to server ===== \n");
    if (shutdown(skt, SHUT_RD) == 0)
        printf("==== Successfully disconnected ! =====\n");
    return 0;
}