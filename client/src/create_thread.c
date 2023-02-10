/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void create_thread(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    if (!myinfo->user_name)
        client_error_unauthorized();
    else if (get_arg_number(myreq->arg) != 2)
        printf("Invalid number of arguments.\n");
    else {
        myreq->arg = add_to_args(myreq->arg, myinfo->channel_name);
        myreq->arg = add_to_args(myreq->arg, myinfo->user_name);
        myreq->arg = add_to_args(myreq->arg, myinfo->team_name);
        if (!check_size(myreq->arg[0], MAX_NAME) ||
        !check_size(myreq->arg[1], MAX_BODY)) {
            printf("Error. Argument(s) size too long\n");
            return;
        }
        cmd = format_cmd_crlf("CANT", myreq->arg);
        write(server_skt, cmd, strlen(cmd));
        free(cmd);
    }
}
