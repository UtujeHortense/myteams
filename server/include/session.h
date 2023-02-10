/*
** EPITECH PROJECT, 2021
** MYTEAMS SERVER
** File description:
** Server session
*/

#ifndef MYTEAMS_SESSION_H
#define MYTEAMS_SESSION_H
#define MAX_NAME 32
#define MAX_DESC 255
#define MAX_BODY 512

typedef struct comment_info
{
    char *user_uuid;
    char message_body[MAX_BODY];
} comment_t;

typedef struct thread_info
{
    char const *thread_uuid;
    char thread_title[MAX_NAME];
    char thread_message[MAX_BODY];
    comment_t **mycomments;
} thread_t;

typedef struct channel_info
{
    char const *chan_uuid;
    char chan_name[MAX_NAME];
    char chan_description[MAX_DESC];
    thread_t **mythreads;
} channel_t;

typedef struct team_info
{
    char const *team_uuid;
    char team_name[MAX_NAME];
    char team_description[MAX_DESC];
    channel_t **mychannels;
} team_t;

typedef struct user_info
{
    char const *user_uuid;
    char user_name[MAX_NAME];
    char **myteams;
} user_t;

typedef struct session_info
{
    user_t **allusers;
    team_t **allteams;
} session_t;

typedef struct count
{
    size_t user_nb;
    size_t te_nb;
    size_t ch_nb;
    size_t th_nb;
    size_t co_nb;
} count_t;

#endif