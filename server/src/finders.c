/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "server.h"

int find_team_index(char *team_name, session_t *allinfo)
{
    const char *team_uuid = NULL;
    int i = 0;
    team_uuid = get_team_uuid(allinfo->allteams, team_name);
    for (; allinfo->allteams[i]; i++) {
        if (strcmp(allinfo->allteams[i]->team_uuid, team_uuid) == 0)
            return i;
    }
    return -1;
}

int find_channel_index(char *chan_name, session_t *allinfo, int i)
{
    const char *chan_uuid = NULL;
    int j = 0;
    chan_uuid = get_channel_uuid(allinfo->allteams[i]->mychannels, chan_name);
    for (; allinfo->allteams[i]->mychannels[j]; j++) {
        if (strcmp(allinfo->allteams[i]->mychannels[j]->chan_uuid,
            chan_uuid) == 0)
            return j;
    }
    return -1;
}

int find_thread_index(char *n, session_t *allinfo, int i, int j)
{
    const char *th = NULL;
    const char *temp = NULL;
    int k = 0;
    th = get_thread_uuid(allinfo->allteams[i]->mychannels[j]->mythreads, n);
    for (; allinfo->allteams[i]->mychannels[j]->mythreads[k]; k++) {
        temp =
        strdup(allinfo->allteams[i]->mychannels[j]->mythreads[k]->thread_uuid);
        if (strcmp(temp, th) == 0)
            return k;
        temp = NULL;
    }
    return -1;
}
