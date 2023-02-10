/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

void accept_incoming_on_control(my_var_t *allvar)
{
    char *message = "200 Connected to MYTEAMS.\n";
    int ret = 0;
    int new_socket = accept(allvar->control_socket,
    (struct sockaddr *)&allvar->other_address, (socklen_t *)&allvar->len);
    if (new_socket < 0)
        exit_with_error("accept");
    ret = write(new_socket, message, strlen(message));
    printf("New client connected, IP :%s Port:%d\n",
    inet_ntoa(allvar->other_address.sin_addr),
    ntohs(allvar->other_address.sin_port));
    if (ret < 0)
        exit_with_error("write");
    add_to_clients(allvar, new_socket);
}

void eval_client_socket(my_var_t *allvar, myfds_t *allfd, int asocket,
session_t *allinfo)
{
    int count = 0;
    char *buff = calloc(3000, sizeof(char));
    if (buff == NULL)
        exit_with_error("malloc");
    memset(buff, 0, strlen(buff));
    if (FD_ISSET(asocket, &allfd->read_sockets)) {
        count = read(asocket, buff, 256);
        if (count < 0)
            exit_with_error("read");
        else if (count > 0) {
            command_managment(allvar, buff, asocket, allinfo);
            memset(buff, 0, strlen(buff));
        }
    }
    free(buff);
}

void check_other_sockets(my_var_t *allvar, myfds_t *allfd, session_t *allinfo)
{
    int asocket;
    for (size_t i = 0; i < FD_SETSIZE; i++) {
        asocket = allvar->my_client_socket[i];
        eval_client_socket(allvar, allfd, asocket, allinfo);
    }
}

void wait_for_activity(my_var_t *allvar, myfds_t *allfd, session_t *allinfo)
{
    int actv;
    actv = select(allvar->max_fd + 1, &allfd->read_sockets, NULL, NULL, NULL);
    if ((actv < 0) && (errno != EINTR))
        exit_with_error("Select failure");
    if (FD_ISSET(allvar->control_socket, &allfd->read_sockets))
        accept_incoming_on_control(allvar);
    else
        check_other_sockets(allvar, allfd, allinfo);
}
