/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

char *add_quotes(const char *str)
{
    char *newstr = NULL;
    newstr = malloc(sizeof(char) * (strlen(str) + 3));
    strcpy(newstr, "\"");
    strcat(newstr, str);
    strcat(newstr, "\"");
    return newstr;
}

char *format_server_response(const char *code, const char *arg)
{
    char *response = NULL;
    response = malloc(sizeof(char) * (strlen(code) + strlen(arg) + 5));
    strcpy(response, add_quotes(code));
    strcat(response, add_quotes(arg));
    return response;
}