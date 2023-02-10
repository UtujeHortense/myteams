/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void is_connected(char **parsed, char *name, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "100");
    name[strlen(name) - 1] = '\0';
    if (ret == 0) {
        client_event_logged_in(parsed[1], parsed[2]);
        if (strcmp(parsed[2], myinfo->user_name) == 0) {
            myinfo->user_uuid = strdup(parsed[1]);
        }
        free_parsed_arg(parsed);
    }
    else
        printf("Error couldn't log in\n");
}

void is_disconnected(char **parsed, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "102");
    if (ret == 0) {
        client_event_logged_out(parsed[1], parsed[2]);
        if (strcmp(parsed[2], myinfo->user_name) == 0){
            free(myinfo->user_name);
            free(myinfo->user_uuid);
        }
        free_parsed_arg(parsed);
    }
    else
        printf("Error couldn't logout in\n");
}

void check_response_cang(char **parsed, req_s *myreq)
{
    (void)myreq;
    int ret = strcmp(parsed[0], "150");
    if (ret == 0){
        if (parsed[4])
            client_print_team_created(parsed[1], parsed[2], parsed[3]);
        client_event_team_created(parsed[1], parsed[2], parsed[3]);
    }
    else if (strcmp(parsed[0], "151") == 0 && parsed[1] != NULL)
        client_error_already_exist();
    else
        printf("Error couldn't create team\n");
}

void check_response_canc(char **parsed, req_s *myreq, path_t *myinfo)
{
    int ret = strcmp(parsed[0], "152");
    if (ret == 0){
        if (parsed[5] != NULL)
            client_print_channel_created(parsed[1],
            myreq->arg[0], myreq->arg[1]);
        if (is_subscribed(parsed[4], myinfo))
            client_event_channel_created(parsed[1], parsed[2], parsed[3]);
    }
    else if (strcmp(parsed[0], "153") == 0 && parsed[1] != NULL)
        client_error_already_exist();
    else
        printf("Error couldn't create channel\n");
}

void check_response_cant(char **parsed, req_s *myreq, path_t *myinfo)
{
    (void)myreq;
    int ret = strcmp(parsed[0], "154");
    time_t time_stamp;
    time(&time_stamp);
    if (ret == 0){
        if (parsed[6] != NULL)
            client_print_thread_created(parsed[1], parsed[2],
            time_stamp, parsed[3], parsed[4]);
        if (is_subscribed(parsed[5], myinfo))
            client_event_thread_created(parsed[1], parsed[2],
            time_stamp, parsed[3], parsed[4]);
    }
    else if (strcmp(parsed[0], "155") == 0 && parsed[1] != NULL)
        client_error_already_exist();
    else
        printf("Error couldn't create thread\n");
}