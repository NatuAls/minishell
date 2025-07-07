#ifndef MINISHELL_H
#	define MINISHELL_H


#	include <errno.h>
#	include <readline/readline.h>
#	include <readline/history.h>
#	include <sys/wait.h>
#	include <signal.h>
#	include "../libft/libft.h"



typedef struct s_mini_sh
{
	int			input;
	pid_t		mypid;
	int			myfd;

}	t_mini_sh;


void ft_error_handler(char *s, int errorcode);
void ft_getinput(t_mini_sh sh);







#	define NRM  "\x1B[0m"
#	define RED  "\x1B[31m"
#	define GRN  "\x1B[32m"
#	define YEL  "\x1B[33m"
#	define BLU  "\x1B[34m"
#	define MAG  "\x1B[35m"
#	define CYN  "\x1B[36m"
#	define WHT  "\x1B[37m"

#endif
