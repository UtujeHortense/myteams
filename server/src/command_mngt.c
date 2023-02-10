/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

req_t parse_request(my_var_t *allvar, char *cmd)
{
    req_t my_request;
    char maincmd[5];
    int n = get_n_val(cmd);
    memset(maincmd, 0, 5);
    strncpy(maincmd, cmd, n);
    my_request.id = 0;
    my_request.arg = f_arguments(cmd, n);
    for (int i = 0; i < CMDSIZE; i++) {
        if (strcmp(allvar->mycmd[i].cmd, maincmd) == 0) {
            my_request.id = allvar->mycmd[i].cmdval;
            my_request.is_valid = true;
            break;
        }
        else
            my_request.is_valid = false;
    }
    return my_request;
}

void command_managment(my_var_t *allvar, char *cmd, int client,
session_t *allinfo)
{
    command_check(cmd);
    req_t myreq = parse_request(allvar, cmd);
    accept_request(allvar, &myreq, client, allinfo);
}