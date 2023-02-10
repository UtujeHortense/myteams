/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-ugo.oger
** File description:
** communication
*/

#include "client.h"

void help_me(req_s *myreq)
{
    if (myreq->is_valid == false || get_arg_number(myreq->arg) != 0)
        printf("Use just </help> instead ;)\n");
    else {
        printf("The following commands are valid : \n\n");
        printf("/help : show help\n");
        printf("/login [“user_name”] : login as a new or old user\n");
        printf("/logout : disconnect from this session\n\n");
        printf("/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]");
        printf(" : use specify a context team/channel/thread\n");
        printf("/create : based on what is being used\n");
    }
}