/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server load from save thread part
*/

#include "server.h"

char *load_thread(char *line, count_t *c, session_t *allinfo, FILE *fd)
{
    char **take_line = f_arguments(line, 8);

    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb] =
    malloc(sizeof(thread_t));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]
    ->mythreads[c->th_nb + 1] = NULL;
    strcpy(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]
    ->mythreads[c->th_nb]->thread_title, take_line[0]);
    strcpy(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]
    ->mythreads[c->th_nb]->thread_message, take_line[2]);
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->thread_uuid = strdup(take_line[1]);
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->mycomments = malloc(sizeof(comment_t *));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->mycomments[0] = NULL;
    if (!(line = parse_comment(allinfo, c, fd)))
        return NULL;
    return line;
}

char *parse_thread(session_t *allinfo, count_t *c, FILE *fd)
{
    size_t len = 0;
    ssize_t read;
    char *line = NULL;

    if ((read = getline(&line, &len, fd)) != -1) {
        while (strncmp(line, "THREADS", 7) == 0) {
            allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads =
            realloc(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]
            ->mythreads, (sizeof(thread_t *) * (c->th_nb + 2)));
            if (!(line = load_thread(line, c, allinfo, fd)))
                return NULL;
            c->th_nb++;
            c->co_nb = 0;
        }
    } else
        return NULL;
    return line;
}
