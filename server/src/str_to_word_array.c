/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** server str_to_word_array
*/

#include "server.h"

char **save_in_array(char **myargs, char *mystr)
{
    char delim[] = "\"";
    char *ptr = strtok(mystr, delim);
    int count = 0;
    for (int i = 0; ptr != NULL; i++) {
        if (strlen(ptr) > 1 || ptr[0] != ' ') {
            myargs = realloc(myargs, (sizeof(char *) * (count + 2)));
            myargs[count] = strdup(ptr);
            count++;
        }
        ptr = strtok(NULL, delim);
    }
    if (myargs == NULL)
        return myargs;
    myargs[count] = NULL;
    return myargs;
}

bool checked_quotes(char *str)
{
    int count = 0;
    if (strlen(str) == 0)
        return true;
    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] == '\"')
            count++;
    if ((count % 2) == 0 && count > 0)
        return true;
    return false;
}

char **f_arguments(char *mystr, size_t n)
{
    size_t len = strlen(mystr);
    char **myargs = NULL;
    if (mystr[n] == ' ')
        n += 1;
    memmove(mystr, mystr + n, len - n + 1);
    if (!checked_quotes(mystr)) {
        myargs = malloc(sizeof(char *) * 1);
        myargs[0] = strdup("err");
        return myargs;
    }
    myargs = save_in_array(myargs, mystr);
    return myargs;
}