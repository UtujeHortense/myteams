/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

static reply_t rep;

void init_thread_reply_struct(reply_t *rep, req_t *myreq, session_t *allinfo)
{
    int t = 0;
    rep->teamid = get_team_uuid(allinfo->allteams, myreq->arg[4]);
    rep->threadid = NULL;
    rep->chanid = NULL;
    rep->userid = get_user_uuid(allinfo->allusers, myreq->arg[3]);
    for (; strcmp(allinfo->allteams[t]->team_uuid, rep->teamid) != 0; t++);
    rep->chanid = get_channel_uuid(allinfo->allteams[t]
    ->mychannels, myreq->arg[2]);
}

char *format_threadrep_to_client(my_var_t *allvar, req_t *myreq,
session_t *allinfo, char *uuid_str)
{
    char *temp = NULL;
    char *response = NULL;
    init_thread_reply_struct(&rep, myreq, allinfo);
    size_t len = strlen(rep.userid) + strlen(rep.chanid) +
    strlen(rep.teamid) + 32;
    response = format_server_response(allvar->mycmd[CANT - 1].info, uuid_str);
    temp = calloc(sizeof(char), (len + strlen(response)));
    strcpy(temp, response);
    strcat(temp, add_quotes(rep.userid));
    strcat(temp, add_quotes(myreq->arg[0]));
    strcat(temp, add_quotes(myreq->arg[1]));
    strcat(temp, add_quotes(rep.teamid));
    return temp;
}

size_t resize_thread_array(session_t *allinfo, size_t i, size_t j)
{
    size_t k = 0;

    for (; allinfo->allteams[i]->mychannels[j]->mythreads[k] != NULL; k++);
    allinfo->allteams[i]->mychannels[j]->mythreads =
    realloc(allinfo->allteams[i]->mychannels[j]->mythreads,
    (sizeof(thread_t *) * (k + 2)));
    allinfo->allteams[i]->mychannels[j]->mythreads[k] =
    malloc(sizeof(thread_t) * 1);
    allinfo->allteams[i]->mychannels[j]->mythreads[k]->mycomments =
    malloc(sizeof(comment_t *));
    allinfo->allteams[i]->mychannels[j]->mythreads[k]->mycomments[0] =
    NULL;
    allinfo->allteams[i]->mychannels[j]->mythreads[k + 1] = NULL;
    return k;
}

void add_new_thread(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    uuid_t uuid;
    size_t i = find_team_index(myreq->arg[4], allinfo);
    size_t j = find_channel_index(myreq->arg[2], allinfo, i);
    size_t k = resize_thread_array(allinfo, i, j);
    char uuid_str[37];

    uuid_generate_time_safe(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    strcpy(allinfo->allteams[i]->mychannels[j]->mythreads[k]
    ->thread_title, myreq->arg[0]);
    strcpy(allinfo->allteams[i]->mychannels[j]->mythreads[k]
    ->thread_message, myreq->arg[1]);
    allinfo->allteams[i]->mychannels[j]->mythreads[k]->thread_uuid =
    strdup(uuid_str);
    server_event_thread_created(allinfo->allteams[i]->mychannels[j]
    ->chan_uuid, uuid_str, get_user_uuid(allinfo->allusers, myreq->arg[3]),
    myreq->arg[0], myreq->arg[1]);
    broadcast_reply_to_users(allvar,
    format_threadrep_to_client(allvar, myreq, allinfo, uuid_str), client);
}

void create_new_thread(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    size_t i = 0;
    size_t j = 0;
    char *response = format_server_response(allvar->mycmd[CANT - 1].err, "");

    if (myreq->id == CANT && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        for (; strcmp(allinfo->allteams[i]->team_name,
        myreq->arg[4]) != 0; i++);
        for (; strcmp(allinfo->allteams[i]->mychannels[j]->chan_name,
        myreq->arg[2]) != 0; j++);
        if (!thread_exists(allinfo->allteams[i]->mychannels[j]->mythreads,
        myreq->arg[0]))
            add_new_thread(allvar, myreq, client, allinfo);
        else {
            format_server_response(allvar->mycmd[CANT -1].err, "thread exist");
            write(client, response, strlen(response));
        }
    }
    else
        write(client, response, strlen(response));
}
