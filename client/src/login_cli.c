/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

int get_arg_number(char **arg)
{
    int count = 0;
    if (arg == NULL)
        return count;
    for (int i = 0; arg[i] != NULL; i++)
        count++;
    return count;
}

char *format_cmd_crlf(char *protocol, char **str)
{
    char *finalcmd = NULL;
    size_t len = 0;
    for (int i = 0; str[i] != NULL; i++)
        len += strlen(str[i]) + 2;
    if (len == 0)
        return protocol;
    finalcmd = malloc(sizeof(char) * (strlen(protocol) + 10 + len));
    strcpy(finalcmd, protocol);
    for (int i = 0; str[i] != NULL; i++) {
        strcat(finalcmd, " ");
        strcat(finalcmd, add_quotes(str[i]));
    }
    strcat(finalcmd, "\r\n");
    return finalcmd;
}

void login_cli(req_s *myreq, int server_skt, path_t *myinfo)
{
    if (myreq->is_valid == false || get_arg_number(myreq->arg) != 1)
        printf("Error with command, Please try again.\n");
    else {
        if (!check_size(myreq->arg[0], MAX_NAME)) {
            printf("Error. Argument size too long\n");
            return;
        }
        myinfo->user_name = strdup(myreq->arg[0]);
        myreq->arg[0] = format_cmd_crlf("LOGI", myreq->arg);
        write(server_skt, myreq->arg[0], strlen(myreq->arg[0]));
    }
}