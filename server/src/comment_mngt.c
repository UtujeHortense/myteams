/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

static reply_t rep;

void init_reply_struct(reply_t *rep, req_t *myreq, session_t *allinfo)
{
    int t = 0;
    int ch = 0;
    rep->teamid = get_team_uuid(allinfo->allteams, myreq->arg[4]);
    rep->threadid = NULL;
    rep->chanid = NULL;
    rep->userid = get_user_uuid(allinfo->allusers, myreq->arg[2]);
    for (; strcmp(allinfo->allteams[t]->team_uuid, rep->teamid) != 0; t++);
    rep->chanid = get_channel_uuid(allinfo->allteams[t]->mychannels,
    myreq->arg[3]);
    for (; strcmp(allinfo->allteams[t]->mychannels[ch]->chan_uuid,
    rep->chanid) != 0; ch++);
    rep->threadid =
    get_thread_uuid(allinfo->allteams[t]->mychannels[ch]->mythreads,
    myreq->arg[1]);
}

char *format_reply_to_client(my_var_t *allvar, req_t *myreq,
session_t *allinfo)
{
    char *temp = NULL;
    char *response = NULL;
    init_reply_struct(&rep, myreq, allinfo);
    size_t len = strlen(rep.userid) + strlen(rep.threadid) +
    strlen(rep.chanid) + strlen(rep.teamid) + 32;
    response = format_server_response(allvar->mycmd[CANR - 1].info,
    myreq->arg[0]);
    temp = calloc(sizeof(char), (len + strlen(response)));
    strcpy(temp, response);
    strcat(temp, add_quotes(rep.userid));
    strcat(temp, add_quotes(rep.teamid));
    strcat(temp, add_quotes(rep.chanid));
    strcat(temp, add_quotes(rep.threadid));
    return temp;
}

size_t resize_comment_array(session_t *allinfo, size_t i, size_t j, size_t k)
{
    size_t lv = 0;
    for (; allinfo->allteams[i]->mychannels[j]->mythreads[k]
    ->mycomments[lv] != NULL; lv++);
    allinfo->allteams[i]->mychannels[j]->mythreads[k]->mycomments =
    realloc(allinfo->allteams[i]->mychannels[j]->mythreads[k]->mycomments,
    (sizeof(comment_t *) * (lv + 2)));
    allinfo->allteams[i]->mychannels[j]->mythreads[k]->mycomments[lv] =
    malloc(sizeof(comment_t) * 1);
    allinfo->allteams[i]->mychannels[j]->mythreads[k]
    ->mycomments[lv + 1] = NULL;
    return lv;
}

void add_new_comment(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    size_t i = find_team_index(myreq->arg[4], allinfo);
    size_t j = find_channel_index(myreq->arg[3], allinfo, i);
    size_t k = find_thread_index(myreq->arg[1], allinfo, i, j);
    size_t lv = resize_comment_array(allinfo, i, j, k);
    allinfo->allteams[i]->mychannels[j]->mythreads[k]->
    mycomments[lv]->user_uuid = strdup(myreq->arg[2]);
    strcpy(allinfo->allteams[i]->mychannels[j]->mythreads[k]->
    mycomments[lv]->message_body, myreq->arg[0]);
    server_event_reply_created(allinfo->allteams[i]->mychannels[j]->
    mythreads[k]->thread_uuid,
    get_user_uuid(allinfo->allusers, myreq->arg[2]), myreq->arg[0]);
    broadcast_reply_to_users(allvar,
    format_reply_to_client(allvar, myreq, allinfo), client);
}

void create_new_comment(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    char *response = format_server_response(allvar->mycmd[CANR - 1].err, "");
    if (myreq->id == CANR && myreq->is_valid == true &&
    user_is_logged(allvar, client)) {
        add_new_comment(allvar, myreq, client, allinfo);
    }
    else
        write(client, response, strlen(response));
}
