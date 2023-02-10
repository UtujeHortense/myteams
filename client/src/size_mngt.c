/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

bool check_size(char *str, size_t max)
{
    size_t len = strlen(str);
    if (len > max)
        return false;
    return true;
}
