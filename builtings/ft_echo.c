#include "includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	flag_n;

	i = 1;
	flag_n = 0;
	if (!args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		i++;
		flag_n = 1;
		if (!args[i])
			return ;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag_n == 0)
		write(STDOUT_FILENO, "\n", 1);
}
