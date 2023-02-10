/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server load from save comment part
*/

#include "server.h"

void load_comment(char *line, count_t *c, session_t *allinfo)
{
    char **take_line = f_arguments(line, 8);
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->mycomments = realloc(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]
    ->mythreads[c->th_nb]->mycomments, (sizeof(comment_t *) * (c->co_nb + 2)));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->mycomments[c->co_nb] = malloc(sizeof(comment_t));
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->mycomments[c->co_nb + 1] = NULL;
    strcpy(allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]
    ->mythreads[c->th_nb]->mycomments[c->co_nb]->message_body, take_line[0]);
    allinfo->allteams[c->te_nb]->mychannels[c->ch_nb]->mythreads[c->th_nb]
    ->mycomments[c->co_nb]->user_uuid = strdup(take_line[1]);
}

char *parse_comment(session_t *allinfo, count_t *c, FILE *fd)
{
    size_t len = 0;
    ssize_t read;
    char *line = NULL;
    while ((read = getline(&line, &len, fd)) != -1) {
        if (strncmp(line, "COMMENT", 7) == 0) {
            load_comment(line, c, allinfo);
            c->co_nb++;
        } else
            return line;
    }
    return NULL;
}