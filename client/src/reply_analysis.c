/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void check_reply_five(char **parsed, int repcode, path_t *myinfo, req_s *myreq)
{
    if (repcode == 156 || repcode == 157)
        check_response_canr(parsed, myreq, myinfo);
    else if (repcode == 130 || repcode == 131)
        check_response_sub(parsed, myreq, myinfo);
    else
        free_parsed_arg(myreq->arg);
}

void check_reply_four(char **parsed, int repcode, path_t *myinfo, req_s *myreq)
{
    if (repcode == 142 || repcode == 143)
        check_response_usec(parsed, myreq, myinfo);
    else if (repcode == 144 || repcode == 145)
        check_response_uset(parsed, myreq, myinfo);
    else
        check_reply_five(parsed, repcode, myinfo, myreq);
}

void check_reply_three(char **parsed, int repcode, path_t *myinfo, req_s *myreq)
{
    if (repcode == 154 || repcode == 155)
        check_response_cant(parsed, myreq, myinfo);
    else if (repcode == 140 || repcode == 141)
        check_response_useg(parsed, myreq, myinfo);
    else
        check_reply_four(parsed, repcode, myinfo, myreq);
}

void check_reply_two(char **parsed, int repcode, path_t *myinfo, req_s *myreq)
{
    if (repcode == 150 || repcode == 151)
        check_response_cang(parsed, myreq);
    else if (repcode == 152 || repcode == 153)
        check_response_canc(parsed, myreq, myinfo);
    else
        check_reply_three(parsed, repcode, myinfo, myreq);
}

void check_reply_code(int socket, path_t *myinfo, req_s *myreq)
{
    char response[256] = " ";
    int ret = 0;
    int repcode = 0;
    while (ret == 0)
        ret = read(socket, &response, sizeof(response));
    char **parsed = fill_arguments(response, 0);
    repcode = atoi(parsed[0]);
    if (repcode == 100 || repcode == 101)
        is_connected(parsed, myreq->arg[0], myinfo);
    else if (repcode == 102 || repcode == 103)
        is_disconnected(parsed, myinfo);
    else
        check_reply_two(parsed, repcode, myinfo, myreq);
}