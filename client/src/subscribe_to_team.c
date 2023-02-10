/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "client.h"

bool is_subscribed(char *teamid, path_t *myinfo)
{
    for (int i = 0; myinfo->subed[i] != NULL; i++)
        if (strcmp(teamid, myinfo->subed[i]) == 0)
            return true;
    return false;
}

void add_to_subscribed(char *teamid, path_t *myinfo)
{
    int i = 0;
    for (; myinfo->subed[i] != NULL; i++);
    myinfo->subed = realloc(myinfo->subed, (sizeof(char*) * (i + 2)));
    myinfo->subed[i] = strdup(teamid);
    myinfo->subed[i + 1] = NULL;
}

void subscribe_to_team(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    if (!myinfo->user_name)
        client_error_unauthorized();
    else if (myreq->is_valid == false || get_arg_number(myreq->arg) != 1
    || !myreq->arg) {
        printf("Error. See /help for correct format\n");
        return;
    }
    else {
        myreq->arg = add_to_args(myreq->arg, myinfo->user_name);
        cmd = format_cmd_crlf("SUB", myreq->arg);
        write(server_skt, cmd, strlen(cmd));
        free(cmd);
    }
}