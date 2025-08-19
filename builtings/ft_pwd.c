#include "includes/minishell.h"

void	ft_pwd(t_mini_sh *sh)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		sh->last_status = 0;
	}
	else
	{
		ft_put_error("pwd", "error retrieving current directory");
		sh->last_status = 1;
	}
}
