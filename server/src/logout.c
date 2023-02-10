/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

void broadcast_log_to_users(my_var_t *allvar, char *temp)
{
    for (int i = 0; i < allvar->max_fd; i++) {
        if (allvar->islogged[i] == true)
            write(allvar->my_client_socket[i],
            temp,
            strlen(temp));
    }
    free(temp);
}

char *format_logoutrep_to_client(my_var_t *allvar, req_t *myreq,
session_t *allinfo)
{
    char *temp = NULL;
    char *response = NULL;
    int i = 0;
    for (; strcmp(allinfo->allusers[i]->user_uuid, myreq->arg[0]) != 0; i++);
    size_t len = strlen(myreq->arg[0]) +
    strlen(allinfo->allusers[i]->user_name) + 32;
    response = format_server_response(allvar->mycmd[LOGOUT - 1].info,
    myreq->arg[0]);
    temp = calloc(sizeof(char), (len + strlen(response)));
    strcpy(temp, response);
    strcat(temp, add_quotes(allinfo->allusers[i]->user_name));
    return temp;
}

void logout(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo)
{
    char *response = NULL;
    response = format_server_response(allvar->mycmd[LOGOUT - 1].err, "");
    if (myreq->id == LOGOUT && myreq->is_valid == true && allvar->islogged) {
        server_event_user_logged_out(myreq->arg[0]);
        response = format_logoutrep_to_client(allvar, myreq, allinfo);
        broadcast_log_to_users(allvar, response);
        update_login_array(allvar, client, false);
    }
    else
        write(client, response, strlen(response));
}