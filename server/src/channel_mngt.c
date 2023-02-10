/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

static reply_t rep;

void init_chan_reply_struct(reply_t *rep, req_t *myreq, session_t *allinfo)
{
    rep->teamid = get_team_uuid(allinfo->allteams, myreq->arg[2]);
    rep->threadid = NULL;
    rep->chanid = NULL;
}

char *format_chanrep_to_client(my_var_t *allvar, req_t *myreq,
session_t *allinfo, char *uuid_str)
{
    char *temp = NULL;
    char *response = NULL;
    init_chan_reply_struct(&rep, myreq, allinfo);
    size_t len = strlen(rep.teamid) + 32;
    response = format_server_response(allvar->mycmd[CANC - 1].info, uuid_str);
    temp = calloc(sizeof(char), (len + strlen(response)));
    strcpy(temp, response);
    strcat(temp, add_quotes(myreq->arg[0]));
    strcat(temp, add_quotes(myreq->arg[1]));
    strcat(temp, add_quotes(rep.teamid));
    return temp;
}

size_t resize_channel_array(session_t *allinfo, size_t i)
{
    size_t j = 0;
    for (; allinfo->allteams[i]->mychannels[j] != NULL; j++);
    allinfo->allteams[i]->mychannels =
    realloc(allinfo->allteams[i]->mychannels, (sizeof(channel_t *) * (j + 2)));
    allinfo->allteams[i]->mychannels[j] = malloc(sizeof(channel_t));
    allinfo->allteams[i]->mychannels[j + 1] = NULL;
    return j;
}

void add_new_channel(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    uuid_t uuid;
    size_t i = find_team_index(myreq->arg[2], allinfo);
    size_t j = resize_channel_array(allinfo, i);
    uuid_generate_time_safe(uuid);
    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);
    strcpy(allinfo->allteams[i]->mychannels[j]->chan_name, myreq->arg[0]);
    strcpy(allinfo->allteams[i]->mychannels[j]->chan_description,
    myreq->arg[1]);
    allinfo->allteams[i]->mychannels[j]->chan_uuid = strdup(uuid_str);
    allinfo->allteams[i]->mychannels[j]->mythreads = malloc(sizeof(thread_t*));
    allinfo->allteams[i]->mychannels[j]->mythreads[0] = NULL;
    server_event_channel_created(allinfo->allteams[i]->team_uuid,
    uuid_str, myreq->arg[0]);
    broadcast_reply_to_users(allvar,
    format_chanrep_to_client(allvar, myreq, allinfo, uuid_str), client);
}

void create_new_channel(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    char *response = format_server_response(allvar->mycmd[CANC - 1].err, "");
    size_t i = 0;
    if (myreq->id == CANC && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        for (; strcmp(allinfo->allteams[i]->team_uuid,
        get_team_uuid(allinfo->allteams, myreq->arg[2])) != 0; i++);
        if (!channel_exists(allinfo->allteams[i]->mychannels, myreq->arg[0]))
            add_new_channel(allvar, myreq, client, allinfo);
        else {
            format_server_response(allvar->mycmd[CANC - 1].err,
            "channel exists");
            write(client, response, strlen(response));
        }
    }
    else
        write(client, response, strlen(response));
}
