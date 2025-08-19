#include "includes/minishell.h"

void	ft_cd(char **args, t_mini_sh *sh)
{
	if (!args[1])
	{
		ft_put_error("cd", "a relative or absolute path is required");
		sh->last_status = 1;
	}
	else if (args[2])
	{
		ft_put_error("cd", "too many arguments");
		sh->last_status = 1;
	}
	else if (chdir(args[1]) != 0)
	{
		ft_put_error(args[1], "No such file or directory");
		sh->last_status = 1;
	}
	else
		sh->last_status = 0;
}
