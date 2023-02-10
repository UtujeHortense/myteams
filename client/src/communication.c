/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

static req_s myreq;

void wait_for_activity(int socket, path_t *myinfo, char *mycmd)
{
    int actv;
    actv = select(myinfo->max_fd + 1, &myinfo->read_sockets, NULL, NULL, NULL);
    if ((actv < 0) && (errno != EINTR))
        perror("Select");
    if (FD_ISSET(STDIN_FILENO, &myinfo->read_sockets)) {
        mycmd = buffer_managment();
        myreq = parse_command(mycmd, socket, myinfo);
    }
    else if (FD_ISSET(socket, &myinfo->read_sockets))
        check_reply_code(socket, myinfo, &myreq);
}

void cli_loop(int socket, path_t myinfo)
{
    char *mycmd = NULL;
    while (1) {
        FD_ZERO(&myinfo.read_sockets);
        FD_ZERO(&myinfo.write_sockets);
        FD_SET(STDIN_FILENO, &myinfo.read_sockets);
        FD_SET(socket, &myinfo.read_sockets);
        myinfo.max_fd = socket;
        wait_for_activity(socket, &myinfo, mycmd);
        mycmd = NULL;
    }
}

bool init_connection(int socket, const char *ip, uint16_t port)
{
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    char response[256] = " ";
    path_t myinfo;
    inet_aton(ip, (struct in_addr *)&serverAddress.sin_addr.s_addr);
    int ret = connect(socket, (struct sockaddr *)&serverAddress,
    sizeof(serverAddress));
    if (ret == -1)
        return false;
    read(socket, &response, sizeof(response));
    printf("%s", response);
    initialize_path(&myinfo);
    cli_loop(socket, myinfo);
    return true;
}