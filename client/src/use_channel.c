/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void use_a_channel(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    char **parsed = NULL;
    int ret = 0;
    char response[256] = " ";
    if (!myinfo->user_name)
        client_error_unauthorized();
    else {
        if (use_a_team(myreq, server_skt, myinfo)) {
            while ((ret = read(server_skt, &response, sizeof(response))) == 0);
            parsed = fill_arguments(response, 0);
            check_response_useg(parsed, myreq, myinfo);
            cmd = format_cmd_crlf("USEC", myreq->arg);
            write(server_skt, cmd, strlen(cmd));
            free(cmd);
        }
    }
}