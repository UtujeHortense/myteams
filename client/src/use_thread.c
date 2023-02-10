/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"
void use_a_thread(req_s *myreq, int server_skt, path_t *myinfo)
{
    char *cmd = NULL;
    char response[256] = " ";
    int ret = 0;
    char **parsed = NULL;
    if (!myinfo->user_name)
        client_error_unauthorized();
    else {
        use_a_channel(myreq, server_skt, myinfo);
        while ((ret = read(server_skt, &response, sizeof(response))) == 0);
        parsed = fill_arguments(response, 0);
        check_response_usec(parsed, myreq, myinfo);
        cmd = format_cmd_crlf("USET", myreq->arg);
        write(server_skt, cmd, strlen(cmd));
        free(cmd);
    }
}