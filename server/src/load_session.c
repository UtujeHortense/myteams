/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server load session
*/

#include "server.h"

char *parse_team(session_t *allinfo, count_t *c, char *line, FILE *fd)
{
    char **take_line = NULL;

    take_line = f_arguments(line, 6);
    allinfo->allteams = realloc(allinfo->allteams,
    (sizeof(team_t *) * (c->te_nb + 2)));
    allinfo->allteams[c->te_nb] = malloc(sizeof(team_t));
    allinfo->allteams[c->te_nb + 1] = NULL;
    strcpy(allinfo->allteams[c->te_nb]->team_name, take_line[0]);
    strcpy(allinfo->allteams[c->te_nb]->team_description, take_line[2]);
    allinfo->allteams[c->te_nb]->team_uuid = strdup(take_line[1]);
    allinfo->allteams[c->te_nb]->mychannels = malloc(sizeof(channel_t *));
    allinfo->allteams[c->te_nb]->mychannels[0] = NULL;
    line = parse_chan(allinfo, c, fd);
    if (!line)
        return NULL;
    c->te_nb++;
    c->ch_nb = 0;
    return line;
}

void init_counter(count_t *counter)
{
    counter->user_nb = 0;
    counter->te_nb = 0;
    counter->ch_nb = 0;
    counter->th_nb = 0;
    counter->co_nb = 0;
}

bool main_load(count_t *counter, session_t *allinfo, FILE *fd, char *line)
{
    while (strncmp(line, "TEAMS", 5) == 0)
        if (!(line = parse_team(allinfo, counter, line, fd)))
            break;
    if (!line)
        return false;
    while (strncmp(line, "USER", 4) == 0)
        if (!(line = parse_user(allinfo, counter, line, fd)))
            break;
    if (line)
        main_load(counter, allinfo, fd, line);
    return true;
}

void parse_save_file(session_t *allinfo)
{
    FILE *fd = fopen("./session_file", "r");
    count_t counter;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    init_counter(&counter);

    if (fd == NULL) {
        printf("Invalid File");
        return;
    }
    while ((read = getline(&line, &len, fd)) != -1)
        if (!main_load(&counter, allinfo, fd, line))
            break;
    if (line)
        free(line);
    fclose(fd);
    fclose(fopen("./session_file", "w"));
}