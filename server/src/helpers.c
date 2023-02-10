/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

char *replacechar(char *ip, char c1, char c2)
{
    int i = 0;
    for (i = 0; ip[i]; i++)
        if (ip[i] == c1)
            ip[i] = c2;
    return ip;
}

char *remove_n_char(char *str, size_t n)
{
    size_t len = strlen(str);
    if (str[n] == ' ')
        n += 1;
    memmove(str, str + n, len - n + 1);
    return str;
}

int get_n_val(char *cmd)
{
    size_t i = 0;
    for (; i < strlen(cmd); i++) {
        if (cmd[i] == ' ' || cmd[i] == '\0')
            break;
    }
    return i;
}