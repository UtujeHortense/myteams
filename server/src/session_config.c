/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server erroh handling
*/

#include "server.h"

bool has_saved_session(void)
{
    if (access("./session_file", F_OK) == 0){
        return true;
    }
    else
        return false;
}

void load_saved_session(session_t *allinfo)
{
    printf("loading saved session..\n");
    allinfo->allusers = malloc(sizeof(user_t *));
    allinfo->allusers[0] = NULL;
    allinfo->allteams = malloc(sizeof(team_t *));
    allinfo->allteams[0] = NULL;
    if (has_saved_session() == true) {
        parse_save_file(allinfo);
    }
    printf("session loaded\n");
}

char *strcat_char(char *dest, char *src, char *val)
{
    strcat(dest, src);
    if (strlen(val) > 0)
        strcat(dest, val);
    return dest;
}

bool save_to_session(const char *str)
{
    FILE *fd = fopen("./session_file", "a");
    fprintf(fd, "%s", str);
    fclose(fd);
    return true;
}