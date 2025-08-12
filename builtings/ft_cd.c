#include "includes/minishell.h"

void	ft_cd(char **args)
{
	if (!args[1])
		ft_put_error("cd", "a relative or absolute path is required");
	else if (args[2])
		ft_put_error("cd", "too many arguments");
	else if (chdir(args[1]) != 0)
		ft_put_error(args[1], "No such file or directory");
}
