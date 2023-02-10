/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void initialize_path(path_t *myinfo)
{
    myinfo->user_name = NULL;
    myinfo->user_uuid = NULL;
    myinfo->team_name = NULL;
    myinfo->team_uuid = NULL;
    myinfo->channel_name = NULL;
    myinfo->channel_uuid = NULL;
    myinfo->thread_title = NULL;
    myinfo->thread_uuid = NULL;
    myinfo->subed = malloc(sizeof(char*));
    myinfo->subed[0] = NULL;
}

bool check_for_crlf(char *cmd)
{
    size_t len = strlen(cmd);
    if (cmd[len - 1] == '\n')
        return true;
    return false;
}

char *buffer_managment(void)
{
    char *mycmd = NULL;
    char newcmd[3000];
    int ret = 0;
    mycmd = read_command();
    while (!check_for_crlf(mycmd)){
        ret = read(STDIN_FILENO, newcmd, 3000);
        if (ret > 0) {
            mycmd = realloc(mycmd, sizeof(char) * (ret + 1));
            strcat(mycmd, newcmd);
            memset(newcmd, 0, 3000);
        }
    }
    return mycmd;
}