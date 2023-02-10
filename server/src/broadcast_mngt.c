/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

void broadcast_reply_to_users(my_var_t *allvar, char *temp, int client)
{
    char *temp2 = NULL;
    (void)client;
    temp2 = calloc(sizeof(char), (strlen(temp) + 10));
    strcpy(temp2, temp);
    strcat(temp2, "\"156\"");
    for (int i = 0; i < allvar->max_fd; i++) {
        if (allvar->islogged[i] == true){
            if (allvar->my_client_socket[i] == client)
                write(client, temp2, strlen(temp2));
            else
                write(allvar->my_client_socket[i], temp, strlen(temp));
        }
    }
    free(temp);
    free(temp2);
}