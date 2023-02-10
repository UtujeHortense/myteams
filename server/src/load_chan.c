/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server load from save channel part
*/

#include "server.h"

char *load_chan(char *line, count_t *c, session_t *allinfo, FILE *fd)
{
    char **take_line = f_arguments(line, 6);
    allinfo->allteams[c->te_nb]->mychannels = realloc(allinfo
    ->allteams[c->te_nb]->mychannels, (sizeof(channel_t *) * (c->ch_nb + 2)));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb] =
    malloc(sizeof(channel_t));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb + 1] = NULL;
    strcpy(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->chan_name,
    take_line[0]);
    strcpy(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->chan_description,
    take_line[2]);
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->chan_uuid =
    strdup(take_line[1]);
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads =
    malloc(sizeof(thread_t *));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[0] = NULL;
    if (!(line = parse_thread(allinfo, c, fd)))
        return NULL;
    return line;
}

char *parse_chan(session_t *allinfo, count_t *c, FILE *fd)
{
    size_t len = 0;
    ssize_t read;
    char *line = NULL;

    if ((read = getline(&line, &len, fd)) != -1) {
        while (strncmp(line, "CHANS", 5) == 0) {
            if (!(line = load_chan(line, c, allinfo, fd)))
                return NULL;
            c->ch_nb++;
            c->th_nb = 0;
        }
    } else
        return NULL;
    return line;
}