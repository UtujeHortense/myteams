/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

char **add_to_args(char **args, char *str)
{
    int i = 0;
    while (args[i] != NULL)
        i++;
    args = realloc(args, sizeof(char *) * (i + 2));
    args[i] = strdup(str);
    args[i + 1] = NULL;
    return args;
}

void create_team(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    if (!myinfo->user_name)
        client_error_unauthorized();
    else if (get_arg_number(myreq->arg) != 2)
        printf("Invalid number of arguments.\n");
    else {
        myreq->arg = add_to_args(myreq->arg, myinfo->user_name);
        if (!check_size(myreq->arg[0], MAX_NAME) ||
        !check_size(myreq->arg[1], MAX_DESC)) {
            printf("Error. Argument(s) size too long\n");
            return;
        }
        cmd = format_cmd_crlf("CANG", myreq->arg);
        write(server_skt, cmd, strlen(cmd));
        free(cmd);
    }
}

void create_all(req_s *myreq, int server_skt, path_t *myinfo)
{
    if (myreq->is_valid == false || get_arg_number(myreq->arg) > 2
    || !myreq->arg) {
        printf("Error. See /help for correct format\n");
        return;
    }
    if (!myinfo->team_name)
        create_team(myreq, server_skt, myinfo);
    else if (!myinfo->channel_name)
        create_channel(myreq, server_skt, myinfo);
    else if (!myinfo->thread_title)
        create_thread(myreq, server_skt, myinfo);
    else create_comment(myreq, server_skt, myinfo);
}