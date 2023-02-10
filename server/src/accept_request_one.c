/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

void accept_use_req(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    switch (myreq->id) {
    case USEG:
        use_team(allvar, myreq, client, allinfo);
        break;
    case USEC:
        use_channel(allvar, myreq, client, allinfo);
        break;
    case USET:
        use_thread(allvar, myreq, client, allinfo);
        break;
    case SUB:
        sub_to_team(allvar, myreq, client, allinfo);
        break;
    default:
        printf("Command not handled\n");
        break;
    }
}

void accept_creation_req(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    switch (myreq->id) {
    case CANC:
        create_new_channel(allvar, myreq, client, allinfo);
        break;
    case CANT:
        create_new_thread(allvar, myreq, client, allinfo);
        break;
    case CANR:
        create_new_comment(allvar, myreq, client, allinfo);
        break;
    default:
        accept_use_req(allvar, myreq, client, allinfo);
        break;
    }
}

void accept_request(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo)
{
    switch (myreq->id) {
    case LOGIN:
        login(allvar, myreq, client, allinfo);
        break;
    case LOGOUT:
        logout(allvar, myreq, client, allinfo);
        break;
    case CANG:
        create_new_team(allvar, myreq, client, allinfo);
        break;
    default:
        accept_creation_req(allvar, myreq, client, allinfo);
        break;
    }
}