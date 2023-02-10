/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** save session
*/

#include "server.h"

void save_user(session_t allinfo)
{
    for (size_t i = 0; allinfo.allusers[i]; i++) {
        save_to_session("USER \"");
        save_to_session(allinfo.allusers[i]->user_name);
        save_to_session("\" \"");
        save_to_session(allinfo.allusers[i]->user_uuid);
        save_to_session("\"\n");
        for (size_t j = 0; allinfo.allusers[i]->myteams[j]; j++) {
            save_to_session("SUB \"");
            save_to_session(allinfo.allusers[i]->myteams[j]);
            save_to_session("\"\n");
        }
        for (size_t j = 0; allinfo.allusers[i]->myteams[j]; j++)
            free(allinfo.allusers[i]->myteams[j]);
        free(allinfo.allusers[i]->myteams);
    }
    for (size_t i = 0; allinfo.allusers[i]; i++)
        free((char*)allinfo.allusers[i]->user_uuid);
}
