/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void free_parsed_arg(char **parsed)
{
    if (parsed == NULL || parsed[0] == NULL)
        return;
    for (int i = 0; parsed[i] != NULL; i++)
        free(parsed[i]);
    free(parsed);
    parsed = NULL;
}