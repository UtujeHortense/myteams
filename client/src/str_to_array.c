/*
** EPITECH PROJECT, 2021
** sockets
** File description:
** server
*/

#include "client.h"

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

char **fill_arguments(char *mystr, size_t n)
{
    size_t len = strlen(mystr);
    char **myargs = NULL;
    if (mystr[n] == ' ')
        n += 1;
    memmove(mystr, mystr + n, len - n + 1);
    if (!check_quotes(mystr)) {
        myargs = malloc(sizeof(char *) * 1);
        myargs[0] = strdup("err");
        return myargs;
    }
    myargs = save_in_array(myargs, mystr);
    return myargs;
}