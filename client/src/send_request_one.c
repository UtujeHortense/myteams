/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void send_request_two(req_s *myreq, int server_skt, path_t *myinfo)
{
    switch (myreq->id) {
    case CREATE:
        create_all(myreq, server_skt, myinfo);
        break;
    case USE:
        use_all(myreq, server_skt, myinfo);
        break;
    case SUB:
        subscribe_to_team(myreq, server_skt, myinfo);
        break;
    default:
        printf("Other commands coming soon. Try /help\n");
        break;
    }
}

void send_request_one(req_s *myreq, int server_skt, path_t *myinfo)
{
    switch (myreq->id) {
    case HELP:
        help_me(myreq);
        break;
    case LOGIN:
        login_cli(myreq, server_skt, myinfo);
        break;
    case LOGOUT:
        logout_cli(myreq, server_skt, myinfo);
        break;
    default:
        send_request_two(myreq, server_skt, myinfo);
    }
}