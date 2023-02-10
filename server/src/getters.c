/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

const char *get_user_uuid(user_t **myusers, char *user_name)
{
    for (int i = 0; myusers[i] != NULL; i++)
        if (strcmp(myusers[i]->user_name, user_name) == 0)
            return myusers[i]->user_uuid;
    return NULL;
}

const char *get_team_uuid(team_t **myteams, char *team_name)
{
    for (int i = 0; myteams[i] != NULL; i++)
        if (strcmp(myteams[i]->team_name, team_name) == 0)
            return myteams[i]->team_uuid;
    return NULL;
}

const char *get_channel_uuid(channel_t **mychans, char *name)
{
    for (int i = 0; mychans[i] != NULL; i++)
        if (strcmp(mychans[i]->chan_name, name) == 0)
            return mychans[i]->chan_uuid;
    return NULL;
}

const char *get_thread_uuid(thread_t **mythreads, char *name)
{
    for (int i = 0; mythreads[i] != NULL; i++)
        if (strcmp(mythreads[i]->thread_title, name) == 0)
            return mythreads[i]->thread_uuid;
    return NULL;
}