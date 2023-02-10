/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

bool team_exists(team_t **myteams, char *team_name)
{
    if (myteams == NULL)
        return false;
    for (int i = 0; myteams[i] != NULL; i++){
        if (strcmp(myteams[i]->team_name, team_name) == 0 ||
            strcmp(myteams[i]->team_uuid, team_name) == 0)
            return true;
    }
    return false;
}

void response_to_users(my_var_t *allvar, req_t *myreq, int client,
char *uuid_str)
{
    char *response;
    char *temp = NULL;
    size_t len = strlen(myreq->arg[0]) + strlen(myreq->arg[1]) + 32;
    response = format_server_response(allvar->mycmd[CANG - 1].info, uuid_str);
    temp = calloc(sizeof(char), (len + strlen(response)));
    strcpy(temp, response);
    strcat(temp, add_quotes(myreq->arg[0]));
    strcat(temp, add_quotes(myreq->arg[1]));
    for (int i = 0; i < allvar->max_fd; i++) {
        if (allvar->my_client_socket[i] == client)
            strcat(temp, "\"150\"");
        if (allvar->islogged[i] == true)
            write(allvar->my_client_socket[i], temp, strlen(temp));
    }
    free(response);
    free(temp);
}

void add_new_team(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    uuid_t uuid;
    int i = 0;
    uuid_generate_time_safe(uuid);
    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);
    while (allinfo->allteams[i] != NULL)
        i++;
    allinfo->allteams = realloc(allinfo->allteams,
    (sizeof(team_t *) * (i + 2)));
    allinfo->allteams[i] = malloc(sizeof(team_t) * 1);
    allinfo->allteams[i + 1] = NULL;
    allinfo->allteams[i]->mychannels = malloc(sizeof(channel_t *));
    allinfo->allteams[i]->mychannels[0] = NULL;
    strcpy(allinfo->allteams[i]->team_name, myreq->arg[0]);
    strcpy(allinfo->allteams[i]->team_description, myreq->arg[1]);
    allinfo->allteams[i]->team_uuid = strdup(uuid_str);
    server_event_team_created(uuid_str, myreq->arg[0],
    get_user_uuid(allinfo->allusers, myreq->arg[2]));
    response_to_users(allvar, myreq, client, uuid_str);
}

void create_new_team(my_var_t *allvar, req_t *myreq,
int client, session_t *allinfo)
{
    char *response = format_server_response(allvar->mycmd[CANG - 1].err, "");
    if (myreq->id == CANG && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        if (!team_exists(allinfo->allteams, myreq->arg[0]))
            add_new_team(allvar, myreq, client, allinfo);
        else {
            response = format_server_response(allvar->mycmd[CANG - 1].err,
            "team exists");
            write(client, response, strlen(response));
        }
    }
    else
        write(client, response, strlen(response));
}
