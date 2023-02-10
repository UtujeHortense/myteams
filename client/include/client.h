/*
** EPITECH PROJECT, 2021
** MYTEAMS CLIENT
** File description:
** Client
*/

#ifndef MYTEAMS_CLIENT_H
#define MYTEAMS_CLIENT_H

#include "../../libs/myteams/logging_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <errno.h>

#define MAX_NAME 32
#define MAX_DESC 255
#define MAX_BODY 512
#define CMDSIZE 6
#define HELP 1
#define LOGIN 2
#define LOGOUT 3
#define CREATE 4
#define USE 5
#define SUB 6

typedef struct cli_command
{
    int id;
    char **arg;
    bool is_valid;
} req_s;

typedef struct allclicommands
{
    char *cmd;
    int cmdval;
} cmd_s;

typedef struct connection_info
{
    char *user_name;
    char *user_uuid;
    char *team_name;
    char *team_uuid;
    char *channel_name;
    char *channel_uuid;
    char *thread_title;
    char *thread_uuid;
    fd_set read_sockets;
    fd_set write_sockets;
    int max_fd;
    char **subed;
} path_t;

void error_handling_client(int ac, char **av);
void usage(bool error);
bool init_connection(int socket, const char *ip, uint16_t port);
char *read_command(void);
req_s parse_command(char *command, int server_socket, path_t *myinfo);
char *replacechar(char *ip, char c1, char c2);
char **fill_arguments(char *str, size_t n);
int get_n_val(char *cmd);
bool command_is_valid(char **args);
void login_cli(req_s *myreq, int server_skt, path_t *myinfo);
void logout_cli(req_s *myreq, int server_skt, path_t *myinfo);
char *add_quotes(char *str);
int get_arg_number(char **arg);
char *format_cmd_crlf(char *protocol, char **str);
void help_me(req_s *myreq);
void create_all(req_s *myreq, int server_skt, path_t *myinfo);
void use_all(req_s *myreq, int server_skt, path_t *myinfo);
char **add_to_args(char **args, char *str);
void create_channel(req_s *myreq, int server_skt, path_t *myinfo);
bool use_a_team(req_s *myreq, int server_skt, path_t *myinfo);
void use_a_channel(req_s *myreq, int server_skt, path_t *myinfo);
void use_a_thread(req_s *myreq, int server_skt, path_t *myinfo);
void create_thread(req_s *myreq, int server_skt, path_t *myinfo);
void initialize_path(path_t *myinfo);
bool check_for_crlf(char *cmd);
char *buffer_managment(void);
void check_reply_code(int socket, path_t *myinfo, req_s *myreq);
void free_parsed_arg(char **parsed);
void is_connected(char **parsed, char *name, path_t *myinfo);
void is_disconnected(char **parsed, path_t *myinfo);
bool check_size(char *str, size_t max);
void check_response_cang(char **parsed, req_s *myreq);
void check_response_cant(char **parsed, req_s *myreq, path_t *myinfo);
void check_response_canc(char **parsed, req_s *myreq, path_t *myinfo);
void check_response_useg(char **parsed, req_s *myreq, path_t *myinfo);
void check_response_usec(char **parsed, req_s *myreq, path_t *myinfo);
void check_response_uset(char **parsed, req_s *myreq, path_t *myinfo);
void send_request_one(req_s *myreq, int server_skt, path_t *myinfo);
bool check_quotes(char *str);
void create_comment(req_s *myreq, int server_skt, path_t *myinfo);
void check_response_canr(char **parsed, req_s *myreq, path_t *myinfo);
void subscribe_to_team(req_s *myreq, int server_skt, path_t *myinfo);
bool is_subscribed(char *teamid, path_t *myinfo);
void add_to_subscribed(char *teamid, path_t *myinfo);
void check_response_sub(char **parsed, req_s *myreq, path_t *myinfo);
#endif