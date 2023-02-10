/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

bool team_valid(req_t *myreq, session_t *allinfo, int client, my_var_t *allvar)
{
    char *response;
    for (int i = 0; allinfo->allteams[i] != NULL; i++)
        if (strcmp(allinfo->allteams[i]->team_uuid, myreq->arg[0]) == 0) {
            response = format_server_response(allvar->mycmd[USEG - 1].info,
            allinfo->allteams[i]->team_name);
            write(client, response, strlen(response));
            return true;
        }
    return false;
}

bool channel_valid(req_t *myreq, session_t *allinfo, int client,
my_var_t *allvar)
{
    char *response;
    size_t i = 0;
    for (; strcmp(allinfo->allteams[i]->team_uuid, myreq->arg[0]) != 0; i++);
    for (size_t j = 0; allinfo->allteams[i]->mychannels[j]; i++)
        if (strcmp(allinfo->allteams[i]->mychannels[j]->chan_uuid,
        myreq->arg[1]) == 0) {
            response = format_server_response(allvar->mycmd[USEC - 1].info,
            allinfo->allteams[i]->mychannels[j]->chan_name);
            write(client, response, strlen(response));
            return true;
        }
    return false;
}

void use_team(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo)
{
    if (myreq->id == USEG && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        if (!team_valid(myreq, allinfo, client, allvar))
            write(client, allvar->mycmd[USEG - 1].err,
            strlen(allvar->mycmd[USEG - 1].err));
    }
    else
        write(client, allvar->mycmd[USEG - 1].err,
        strlen(allvar->mycmd[USEG - 1].err));
}

void use_channel(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    if (myreq->id == USEC && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        if (!channel_valid(myreq, allinfo, client, allvar))
            write(client, allvar->mycmd[USEC - 1].err,
            strlen(allvar->mycmd[USEC - 1].err));
    }
    else
        write(client, allvar->mycmd[USEC - 1].err,
        strlen(allvar->mycmd[USEC - 1].err));
}