/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server load user
*/

#include "server.h"

void load_sub(count_t *c, char *line, size_t nb_sub_team, session_t *allinfo)
{
    char **take_line = f_arguments(line, 4);

    allinfo->allusers[c->user_nb]->myteams = realloc(allinfo
    ->allusers[c->user_nb]->myteams, (sizeof(char *) * (nb_sub_team + 2)));
    allinfo->allusers[c->user_nb]->myteams[nb_sub_team] = strdup(take_line[0]);
    allinfo->allusers[c->user_nb]->myteams[nb_sub_team + 1] = NULL;
}

char *parse_sub(count_t *c, session_t *allinfo, FILE *fd)
{
    size_t len = 0;
    ssize_t read;
    size_t nb_sub_team = 0;
    char *line = NULL;

    while ((read = getline(&line, &len, fd)) != -1) {
        if (strncmp(line, "SUB", 3) == 0) {
            load_sub(c, line, nb_sub_team, allinfo);
            nb_sub_team++;
        } else
            return line;
    }
    return NULL;
}

char *parse_user(session_t *allinfo, count_t *counter, char *line, FILE *fd)
{
    char **take_line = NULL;
    take_line = f_arguments(line, 5);
    allinfo->allusers = realloc(allinfo->allusers,
    (sizeof(user_t *) * (counter->user_nb + 2)));
    allinfo->allusers[counter->user_nb] = malloc(sizeof(user_t));
    allinfo->allusers[counter->user_nb + 1] = NULL;
    strcpy(allinfo->allusers[counter->user_nb]->user_name, take_line[0]);
    allinfo->allusers[counter->user_nb]->user_uuid = strdup(take_line[1]);
    allinfo->allusers[counter->user_nb]->myteams = malloc(sizeof(char *));
    allinfo->allusers[counter->user_nb]->myteams[0] = NULL;
    if (!(line = parse_sub(counter, allinfo, fd)))
        return NULL;
    counter->user_nb++;
    return line;
}