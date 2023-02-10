/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "client.h"

char *replacechar(char *ip, char c1, char c2)
{
    int i = 0;
    for (i = 0; ip[i]; i++)
        if (ip[i] == c1)
            ip[i] = c2;
    return ip;
}

char *add_quotes(char *str)
{
    char *newstr = NULL;
    newstr = malloc(sizeof(char) * (strlen(str) + 3));
    strcpy(newstr, "\"");
    strcat(newstr, str);
    strcat(newstr, "\"");
    return newstr;
}

bool check_quotes(char *str)
{
    int count = 0;
    if (strlen(str) == 0)
        return true;
    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] == '\"')
            count++;
    if ((count % 2) == 0 && count > 0)
        return true;
    return false;
}

int get_n_val(char *cmd)
{
    size_t i = 0;
    for (; i < strlen(cmd); i++)
        if (cmd[i] == ' ' || cmd[i] == '\0')
            break;
    return i;
}
