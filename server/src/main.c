/*
** EPITECH PROJECT, 2021
** MYTEAMS
** File description:
** main function
*/

#include "server.h"

static session_t allinfo;

cmd_t mycommands[] = {{"HELP", HELP, "", ""},
    {"LOGI", LOGIN, "100", "101"},
    {"LOGO", LOGOUT, "102", "103"},
    {"CANG", CANG, "150", "151"},
    {"USEG", USEG, "140", "141"},
    {"CANC", CANC, "152", "153"},
    {"USEC", USEC, "142", "143"},
    {"CANT", CANT, "154", "155"},
    {"USET", USET, "144", "145"},
    {"CANR", CANR, "156", "157"},
    {"SUB", SUB, "130", "131"}};

static void sighdl(int sig, siginfo_t *siginfo, void *context)
{
    (void)sig;
    (void)siginfo;
    (void)context;
    printf("\n%s\n", "Saving current session..");
    save_session(allinfo);
    printf("%s\n", "session saved. Good bye");
    exit(0);
}

void catch_signal(void)
{
    struct sigaction act;
    memset(&act, '\0', sizeof(act));
    act.sa_sigaction = &sighdl;
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &act, NULL) < 0)
        perror("sigaction");
}

void initialize_mydata(my_var_t *allvar, char **av)
{
    for (size_t i = 0; i < FD_SETSIZE; i++)
        allvar->my_client_socket[i] = 0;
    allvar->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (allvar->control_socket == 0)
        exit_with_error("socket failure");
    allvar->ctl_address.sin_family = AF_INET;
    allvar->ctl_address.sin_port = htons(atoi(av[1]));
    allvar->ctl_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(allvar->control_socket, (struct sockaddr *)&allvar->ctl_address,
    sizeof(allvar->ctl_address));
    if (listen(allvar->control_socket, FD_SETSIZE) < 0)
        exit_with_error("Listen tapped out");
    allvar->len = 0;
    memset(allvar->islogged, false, FD_SETSIZE);
    allvar->mycmd = mycommands;
}

int main(int ac, char **av)
{
    my_var_t allvar;
    myfds_t allfd;
    load_saved_session(&allinfo);
    error_handling_server(ac, av);
    initialize_mydata(&allvar, av);
    has_saved_session();
    while (1) {
        catch_signal();
        FD_ZERO(&allfd.read_sockets);
        FD_ZERO(&allfd.write_sockets);
        FD_SET(allvar.control_socket, &allfd.read_sockets);
        allvar.max_fd = allvar.control_socket;
        add_to_fdset(&allvar, &allfd);
        wait_for_activity(&allvar, &allfd, &allinfo);
    }
    close(allvar.control_socket);
    return 0;
}