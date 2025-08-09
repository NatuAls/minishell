#include "includes/minishell.h"
#include <signal.h>

void handle_sig_c(int sig)
{
    (void)sig;
    printf("\nmi Ctrl C  \n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sig_quit(int sig)
{
    (void)sig;
    printf("\nno hace nada\n");
    rl_on_new_line();
    rl_redisplay();
}

void ft_setup_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = handle_sig_c;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;

    sa_quit.sa_handler = handle_sig_quit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa_int, NULL);    // Ctrl+C
    sigaction(SIGQUIT, &sa_quit, NULL);  // Ctrl+ barra
}