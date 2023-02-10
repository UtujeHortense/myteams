/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

void add_subscribed(session_t *allinfo, req_t *myreq)
{
    int i = 0;
    int j = 0;
    for (; allinfo->allusers[i] != NULL; i++)
        if (strcmp(allinfo->allusers[i]->user_name, myreq->arg[1]) == 0)
            break;
    for (;allinfo->allusers[i]->myteams[j] != NULL; j++){
        if (strcmp(allinfo->allusers[i]->myteams[j], myreq->arg[0]) == 0)
            return;
    }
    allinfo->allusers[i]->myteams = realloc(allinfo->allusers[i]->myteams,
    (sizeof(char *) * (j + 2)));
    allinfo->allusers[i]->myteams[j] = strdup(myreq->arg[0]);
    allinfo->allusers[i]->myteams[j + 1] = NULL;
}

void sub_to_team(my_var_t *allvar, req_t *myreq,
int client, session_t *allinfo)
{
    char *response = format_server_response(allvar->mycmd[SUB - 1].err, "");
    if (myreq->id == SUB && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        if (!team_exists(allinfo->allteams, myreq->arg[0]))
            write(client, response, strlen(response));
        else {
            server_event_user_subscribed(myreq->arg[0],
            get_user_uuid(allinfo->allusers, myreq->arg[1]));
            add_subscribed(allinfo, myreq);
            response = format_server_response(allvar->mycmd[SUB - 1].info, "");
            write(client, response, strlen(response));
        }
    }
    else
        write(client, response, strlen(response));
}