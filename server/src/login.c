/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

bool user_is_logged(my_var_t *allvar, int client)
{
    for (size_t i = 0; i < FD_SETSIZE; i++)
        if (allvar->my_client_socket[i] == client)
            return allvar->islogged[i];
    return false;
}

void update_login_array(my_var_t *allvar, int client, bool status)
{
    for (size_t i = 0; i < FD_SETSIZE; i++) {
        if (allvar->my_client_socket[i] == client) {
            allvar->islogged[i] = status;
            break;
        }
    }
}

char *format_logrep_to_client(my_var_t *allvar, char *name,
const char *uuid_str)
{
    char *temp = NULL;
    char *response = NULL;
    size_t len = strlen(name) + 32;
    response = format_server_response(allvar->mycmd[LOGIN - 1].info, uuid_str);
    temp = calloc(sizeof(char), (len + strlen(response)));
    strcpy(temp, response);
    strcat(temp, add_quotes(name));
    return temp;
}

void create_new_user(my_var_t *allvar, int client, req_t *myreq,
session_t *allinfo)
{
    uuid_t uuid;
    int i = 0;
    char *response = NULL;
    uuid_generate_time_safe(uuid);
    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);
    for (; allinfo->allusers[i] != NULL; i++);
    allinfo->allusers = realloc(allinfo->allusers,
    (sizeof(user_t *) * (i + 2)));
    allinfo->allusers[i] = malloc(sizeof(user_t) * 1);
    allinfo->allusers[i + 1] = NULL;
    allinfo->allusers[i]->myteams = malloc(sizeof(char*));
    allinfo->allusers[i]->myteams[0] = NULL;
    strcpy(allinfo->allusers[i]->user_name, myreq->arg[0]);
    allinfo->allusers[i]->user_uuid = strdup(uuid_str);
    update_login_array(allvar, client, true);
    server_event_user_created(uuid_str, myreq->arg[0]);
    server_event_user_logged_in(allinfo->allusers[i]->user_uuid);
    response = format_logrep_to_client(allvar, myreq->arg[0], uuid_str);
    broadcast_log_to_users(allvar, response);
}

void login(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo)
{
    char *response = NULL;
    response = format_server_response(allvar->mycmd[LOGIN - 1].err, "");
    if (myreq->id == LOGIN && myreq->is_valid == true && (myreq->arg != NULL)){
        if (!user_exists(allinfo->allusers, myreq->arg[0], client, allvar))
            create_new_user(allvar, client, myreq, allinfo);
    }
    else
        write(client, response, strlen(response));
}
