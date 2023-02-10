/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

bool thread_valid(req_t *myreq, session_t *allinfo, int client,
my_var_t *allvar)
{
    char *response;
    size_t i = 0;
    size_t j = 0;
    for (; strcmp(allinfo->allteams[i]->team_uuid, myreq->arg[0]) != 0; i++);
    for (; strcmp(allinfo->allteams[i]->mychannels[j]->chan_uuid,
    myreq->arg[1]) != 0; j++);
    for (size_t k = 0; allinfo->allteams[i]->mychannels[j]->mythreads[k]; k++) {
        if (strcmp(allinfo->allteams[i]->mychannels[j]->mythreads[k]->
        thread_uuid, myreq->arg[2]) == 0) {
            response = format_server_response(allvar->mycmd[USET - 1].info,
            allinfo->allteams[i]->mychannels[j]->mythreads[k]->thread_title);
            write(client, response, strlen(response));
            return true;
        }
    }

    return false;
}

void use_thread(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo)
{
    printf("USE THREAD");
    if (myreq->id == USET && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        if (!thread_valid(myreq, allinfo, client, allvar))
            write(client, allvar->mycmd[USET - 1].err,
            strlen(allvar->mycmd[USET - 1].err));
    }
    else
        write(client, allvar->mycmd[USET - 1].err,
        strlen(allvar->mycmd[USET - 1].err));
}