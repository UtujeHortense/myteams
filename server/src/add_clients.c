/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

void add_to_fdset(my_var_t *allvar, myfds_t *allfd)
{
    for (int i = 0; i < allvar->max_fd; i++) {
        if (allvar->my_client_socket[i] > 0)
            FD_SET(allvar->my_client_socket[i], &allfd->read_sockets);
        if (allvar->my_client_socket[i] > allvar->max_fd)
            allvar->max_fd = allvar->my_client_socket[i];
    }
}

void add_to_clients(my_var_t *allvar, int newsocket)
{
    for (size_t i = 0; i < FD_SETSIZE; i++) {
        if (allvar->my_client_socket[i] == 0) {
            allvar->my_client_socket[i] = newsocket;
            allvar->islogged[i] = false;
            break;
        }
    }
}

void remove_from_clients(my_var_t *allvar, int oldsocket)
{
    for (size_t i = 0; i < FD_SETSIZE; i++) {
        if (allvar->my_client_socket[i] == oldsocket) {
            allvar->my_client_socket[i] = 0;
            allvar->islogged[i] = false;
            break;
        }
    }
}