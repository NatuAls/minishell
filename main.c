#include "includes/minishell.h"


void ft_error_handler(char *s, int errorcode)
{
	ft_printf("%s",s);
	exit(errorcode);
}
//

void ft_getinput(t_mini_sh sh)
{
	char *input;

	(void)sh;	
	while (1)
	{
				input = readline(GRN "Minishell$>" NRM);
				if (!input)
						ft_error_handler("input error",1);
				if (input[0] == ' ' || input[0] =='\0')
				{
						free(input);
						ft_printf("");
				}
				else 
				{
					add_history(input);

					ft_printf("Has escrito " BLU "%s\n" NRM,input);
				}
	}


}



//int	main(int argc, char**argv,char **env)
int	main(void)
{
	t_mini_sh shell;	

	shell.mypid = getpid();
	shell.input = 0;
	shell.myfd = 1;	
	ft_getinput(shell);

}
