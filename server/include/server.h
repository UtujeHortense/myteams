/*
** EPITECH PROJECT, 2021
** MYTEAMS SERVER
** File description:
** Server
*/

#ifndef MYTEAMS_SERVER_H
#define MYTEAMS_SERVER_H

#include "../../libs/myteams/logging_server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <uuid/uuid.h>
#include <signal.h>
#include "session.h"
#define CMDSIZE 11
#define HELP 1
#define LOGIN 2
#define LOGOUT 3
#define CANG 4
#define USEG 5
#define CANC 6
#define USEC 7
#define CANT 8
#define USET 9
#define CANR 10
#define SUB 11

typedef struct sockets_fd
{
    fd_set read_sockets;
    fd_set write_sockets;
} myfds_t;

typedef struct allcommands
{
    char *cmd;
    int cmdval;
    char *info;
    char *err;
} cmd_t;

typedef struct requests
{
    int id;
    char **arg;
    bool is_valid;
} req_t;

typedef struct my_variables
{
    int control_socket;
    int data_socket;
    int my_client_socket[FD_SETSIZE];
    int max_fd;
    struct sockaddr_in ctl_address;
    struct sockaddr_in other_address;
    socklen_t len;
    bool islogged[FD_SETSIZE];
    cmd_t *mycmd;
} my_var_t;

typedef struct reply_mngt
{
    const char *teamid;
    const char *threadid;
    const char *chanid;
    const char *userid;
} reply_t;

int error_handling_server(int ac, char **av);
void exit_with_error(char *errmsg);
void command_check(char *cmd);
void accept_incoming_on_control(my_var_t *allvar);
void eval_client_socket(my_var_t *allvar, myfds_t *allfd,
int asocket, session_t *allinfo);
void check_other_sockets(my_var_t *allvar, myfds_t *allfd, session_t *allinfo);
void wait_for_activity(my_var_t *allvar, myfds_t *allfd, session_t *allinfo);
void add_to_fdset(my_var_t *allvar, myfds_t *allfd);
void add_to_clients(my_var_t *allvar, int newsocket);
void remove_from_clients(my_var_t *allvar, int oldsocket);
bool has_saved_session(void);
bool save_to_session(const char *str);
void load_saved_session(session_t *allinfo);
char *format_session_param(void *param, int type);
char *replacechar(char *ip, char c1, char c2);
char *remove_n_char(char *str, size_t n);
int get_n_val(char *cmd);
void command_managment(my_var_t *allvar, char *cmd, int client,
session_t *info);
void login(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo);
void logout(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo);
void update_login_array(my_var_t *allvar, int client, bool status);
bool user_is_logged(my_var_t *allvar, int client);
void create_new_team(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
const char *get_user_uuid(user_t **myusers, char *user_name);
const char *get_team_uuid(team_t **myteams, char *team_name);
char *format_server_response(const char *code, const char *arg);
void use_team(my_var_t *allvar, req_t *myreq, int client, session_t *allinfo);
void create_new_channel(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
void use_channel(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
const char *get_channel_uuid(channel_t **mychans, char *name);
void create_new_thread(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
void use_thread(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
char *add_quotes(const char *str);
const char *get_thread_uuid(thread_t **mythreads, char *name);
void create_new_comment(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
bool team_exists(team_t **myteams, char *team_name);
void sub_to_team(my_var_t *allvar, req_t *myreq,
int client, session_t *allinfo);
char **save_in_array(char **myargs, char *mystr);
bool checked_quotes(char *str);
char **f_arguments(char *mystr, size_t n);
void load_comment(char *line, count_t *c, session_t *allinfo);
char *parse_comment(session_t *allinfo, count_t *c, FILE *fd);
char *load_thread(char *line, count_t *c, session_t *allinfo, FILE *fd);
char *parse_thread(session_t *allinfo, count_t *c, FILE *fd);
char *load_chan(char *line, count_t *c, session_t *allinfo, FILE *fd);
char *parse_chan(session_t *allinfo, count_t *c, FILE *fd);
char *parse_user(session_t *allinfo, count_t *counter, char *line, FILE *fd);
char *parse_team(session_t *allinfo, count_t *c, char *line, FILE *fd);
void parse_save_file(session_t *allinfo);
void init_counter(count_t *counter);
bool main_load(count_t *counter, session_t *allinfo, FILE *fd, char *line);
void broadcast_log_to_users(my_var_t *allvar, char *temp);
void save_session(session_t allinfo);
void save_user(session_t allinfo);
void save_comment(session_t allinfo, size_t i, size_t j, size_t k);
void save_thread(session_t allinfo, size_t i, size_t j);
void save_channel(session_t allinfo, size_t i);
void save_team(session_t allinfo);
bool user_exists(user_t **myusers, char *user_name, int client,
my_var_t *allvar);
void broadcast_reply_to_users(my_var_t *allvar, char *temp, int client);
int find_team_index(char *team_name, session_t *allinfo);
int find_channel_index(char *chan_name, session_t *allinfo, int i);
int find_thread_index(char *n, session_t *allinfo, int i, int j);
char *format_logrep_to_client(my_var_t *allvar, char *name,
const char *uuid_str);
bool thread_exists(thread_t **mythr, char *name);
bool channel_exists(channel_t **mychan, char *name);
void accept_request(my_var_t *allvar, req_t *myreq, int client,
session_t *allinfo);
#endif