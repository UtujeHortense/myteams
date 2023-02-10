/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** PARSE COMMANDS
*/

#include "client.h"

cmd_s mycmd[] = {{"/help", HELP},
    {"/login", LOGIN},
    {"/logout", LOGOUT},
    {"/create", CREATE},
    {"/use", USE},
    {"/subscribe", SUB}};

char *add_crlf(char *cmd)
{
    char *newcmd = calloc(sizeof(char), (strlen(cmd) + 4));
    strcpy(newcmd, cmd);
    newcmd[strlen(newcmd) - 1] = '\r';
    newcmd[strlen(newcmd)] = '\n';
    free(cmd);
    return newcmd;
}

char *read_command(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, stdin)) != -1)
        return line;
    if (nread == -1)
        exit(0);
    return NULL;
}

req_s get_parsed_command(char *cmd)
{
    req_s my_request;
    my_request.id = 0;
    char maincmd[13];
    int n = get_n_val(cmd);
    memset(maincmd, 0, 13);
    strncpy(maincmd, cmd, n);
    my_request.arg = fill_arguments(cmd, n);
    for (int i = 0; i < CMDSIZE; i++) {
        if (strcmp(mycmd[i].cmd, maincmd) == 0 &&
        command_is_valid(my_request.arg)) {
            my_request.id = mycmd[i].cmdval;
            my_request.is_valid = true;
            break;
        }
        else
            my_request.is_valid = false;
    }
    return my_request;
}

req_s parse_command(char *command, int server_skt, path_t *myinfo)
{
    size_t len = strlen(command);
    if (command[len - 2] == '\r')
        command[len - 2] = '\0';
    else {
        command[len - 1] = '\0';
    }
    req_s myreq = get_parsed_command(command);
    send_request_one(&myreq, server_skt, myinfo);
    return myreq;
}
