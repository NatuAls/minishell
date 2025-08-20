#include "includes/minishell.h"
#include <signal.h>

volatile sig_atomic_t g_signal_vol = 0;

void handle_sig_c(int sig)
{
    (void)sig;
    g_signal_vol = 1;
    printf("\n");
    if (rl_line_buffer && rl_line_buffer[0] == '\0') 
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void handle_sig_quit(int sig)
{
    (void)sig;
    printf("\nno hace nada\n");
    g_signal_vol = SIGQUIT;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


void ft_setup_own(void)
{
// Restaurar señales en el hijo
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
        printf("Error setting SIGINT handler\n");
    sigaction(SIGQUIT, &sa, NULL);


}


void ft_setup_signals()
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





/*

tcsetattr(int fd, int optional_actions, const struct termios *termios_p)

Qué hace: Cambia la configuración del terminal a la que pongas en termios_p.

optional_actions define cuándo aplicar el cambio:

TCSANOW → inmediato.

TCSADRAIN → espera a vaciar salida antes de aplicar.

TCSAFLUSH → como TCSADRAIN pero también limpia la entrada pendiente.

Retorno: 0 si va bien, -1 en error.

Ejemplo: desactivar eco de control (^C, ^\):

struct termios term;
tcgetattr(STDIN_FILENO, &term);
term.c_lflag &= ~ECHOCTL;  // oculta ^C, ^\
tcsetattr(STDIN_FILENO, TCSANOW, &term);

*/