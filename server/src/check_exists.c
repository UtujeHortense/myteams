/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

bool user_exists(user_t **myusers, char *user_name, int client,
my_var_t *allvar)
{
    char *response = NULL;
    if (myusers == NULL)
        return false;
    for (int i = 0; myusers[i] != NULL; i++)
        if (strcmp(myusers[i]->user_name, user_name) == 0) {
            update_login_array(allvar, client, true);
            server_event_user_logged_in(myusers[i]->user_uuid);
            response = format_logrep_to_client(allvar, user_name,
            myusers[i]->user_uuid);
            broadcast_log_to_users(allvar, response);
            return true;
        }
    return false;
}

bool thread_exists(thread_t **mythr, char *name)
{
    if (mythr == NULL)
        return false;
    for (int i = 0; mythr[i] != NULL; i++)
        if (strcmp(mythr[i]->thread_title, name) == 0)
            return true;
    return false;
}

bool channel_exists(channel_t **mychan, char *name)
{
    if (mychan == NULL)
        return false;
    for (int i = 0; mychan[i] != NULL; i++)
        if (strcmp(mychan[i]->chan_name, name) == 0)
            return true;
    return false;
}