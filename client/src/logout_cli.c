/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void logout_cli(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    if (myreq->is_valid == false || get_arg_number(myreq->arg) != 0)
        printf("Error with command, Please try again.\n");
    else {
        if (!myinfo->user_uuid){
            client_error_unauthorized();
            return;
        }
        myreq->arg = malloc(sizeof(char *) * 2);
        myreq->arg[0] = strdup(myinfo->user_uuid);
        myreq->arg[1] = NULL;
        cmd = format_cmd_crlf("LOGO", myreq->arg);
        write(server_skt, cmd, strlen(cmd));
        free(cmd);
    }
}