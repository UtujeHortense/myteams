/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void use_no_param(path_t *myinfo)
{
    myinfo->team_name = NULL;
    myinfo->team_uuid = NULL;
    myinfo->channel_name = NULL;
    myinfo->channel_uuid = NULL;
    myinfo->thread_title = NULL;
    myinfo->thread_uuid= NULL;
}

bool use_a_team(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    if (!myinfo->user_name)
        client_error_unauthorized();
    else if (!is_subscribed(myreq->arg[0], myinfo)) {
        printf("Error. You are not subscribed to this team\n");
        return false;
    }
    else {
        cmd = format_cmd_crlf("USEG", myreq->arg);
        write(server_skt, cmd, strlen(cmd));
        free(cmd);
    }
    return true;
}

void use_all(req_s *myreq, int server_skt, path_t *myinfo)
{
    if (myreq->is_valid == false || get_arg_number(myreq->arg) > 3) {
        printf("Error. See /help for correct format\n");
        return;
    }
    if (get_arg_number(myreq->arg) == 1)
        use_a_team(myreq, server_skt, myinfo);
    else if (get_arg_number(myreq->arg) == 2)
        use_a_channel(myreq, server_skt, myinfo);
    else if (get_arg_number(myreq->arg) == 3)
        use_a_thread(myreq, server_skt, myinfo);
    else
        use_no_param(myinfo);
}