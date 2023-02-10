/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** save session
*/

#include "server.h"

void save_comment(session_t allinfo, size_t i, size_t j, size_t k)
{
    for (size_t m = 0; allinfo.allteams[i]->mychannels[j]->mythreads[k]
    ->mycomments[m]; m++) {
        save_to_session("COMMENT \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->mythreads[k]
        ->mycomments[m]->message_body);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->mythreads[k]
        ->mycomments[m]->user_uuid);
        save_to_session("\"\n");
    }
    for (size_t m = 0; allinfo.allteams[i]->mychannels[j]->mythreads[k]
    ->mycomments[m]; m++)
        free(allinfo.allteams[i]->mychannels[j]->mythreads[k]->mycomments[m]
        ->user_uuid);
}

void save_thread(session_t allinfo, size_t i, size_t j)
{
    for (size_t k = 0; allinfo.allteams[i]->mychannels[j]->mythreads[k]; k++) {
        save_to_session("THREADS \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->mythreads[k]
        ->thread_title);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->mythreads[k]
        ->thread_uuid);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->mythreads[k]
        ->thread_message);
        save_to_session("\"\n");
        save_comment(allinfo, i, j, k);
        free(allinfo.allteams[i]->mychannels[j]->mythreads[k]->mycomments);
    }
    for (size_t k = 0; allinfo.allteams[i]->mychannels[j]->mythreads[k]; k++)
        free((char *)allinfo.allteams[i]->mychannels[j]->mythreads[k]->thread_uuid);
}

void save_channel(session_t allinfo, size_t i)
{
    for (size_t j = 0; allinfo.allteams[i]->mychannels[j]; j++) {
        save_to_session("CHANS \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->chan_name);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->chan_uuid);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->mychannels[j]->chan_description);
        save_to_session("\"\n");
        save_thread(allinfo, i, j);
        free(allinfo.allteams[i]->mychannels[j]->mythreads);
    }
    for (size_t j = 0; allinfo.allteams[i]->mychannels[j]; j++)
        free((char *)allinfo.allteams[i]->mychannels[j]->chan_uuid);
}

void save_team(session_t allinfo)
{
    for (size_t i = 0; allinfo.allteams[i]; i++) {
        save_to_session("TEAMS \"");
        save_to_session(allinfo.allteams[i]->team_name);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->team_uuid);
        save_to_session("\" \"");
        save_to_session(allinfo.allteams[i]->team_description);
        save_to_session("\"\n");
        save_channel(allinfo, i);
        free(allinfo.allteams[i]->mychannels);
    }
    for (size_t i = 0; allinfo.allteams[i]; i++)
        free((char *)allinfo.allteams[i]->team_uuid);
}

void save_session(session_t allinfo)
{
    save_user(allinfo);
    save_team(allinfo);
    free(allinfo.allteams);
    free(allinfo.allusers);
}