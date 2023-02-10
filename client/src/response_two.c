/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void check_response_useg(char **parsed, req_s *myreq, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "140");

    if (ret == 0) {
        myinfo->team_name = strdup(parsed[1]);
        myinfo->team_uuid = strdup(myreq->arg[0]);
        myinfo->channel_name = NULL;
        myinfo->channel_uuid = NULL;
        printf("you are now in %s team\n", myinfo->team_name);
    }
    else
        client_error_unknown_team(myreq->arg[0]);
}

void check_response_usec(char **parsed, req_s *myreq, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "142");

    if (ret == 0) {
        myinfo->channel_name = strdup(parsed[1]);
        myinfo->channel_uuid = strdup(myreq->arg[1]);
        myinfo->thread_title= NULL;
        myinfo->thread_uuid = NULL;
        printf("you are now in %s channel\n", myinfo->channel_name);
    }
    else
        client_error_unknown_channel(myreq->arg[1]);
}

void check_response_uset(char **parsed, req_s *myreq, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "144");

    if (ret == 0) {
        myinfo->thread_title = strdup(parsed[1]);
        myinfo->thread_uuid = strdup(myreq->arg[2]);
        printf("you are now in %s thread\n", myinfo->thread_title);
    }
    else
        client_error_unknown_thread(myreq->arg[2]);
}

void check_response_canr(char **parsed, req_s *myreq, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "156");
    
    time_t time_stamp;
    time(&time_stamp);
    if (ret == 0){
        if (parsed[6]!= NULL){
            client_print_reply_created(myinfo->thread_uuid,
            myinfo->user_uuid, time_stamp, myreq->arg[0]);
        }
        if (is_subscribed(parsed[3], myinfo))
            client_event_thread_reply_received(parsed[3],
            parsed[5], parsed[2], parsed[1]);
    }
    else printf("Error couldn't create comment\n");
}

void check_response_sub(char **parsed, req_s *myreq, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "130");
    if (ret == 0) {
        add_to_subscribed(myreq->arg[0], myinfo);
        client_print_subscribed(myinfo->user_uuid, myreq->arg[0]);
    }
    else
        client_error_unknown_team(myreq->arg[0]);
}