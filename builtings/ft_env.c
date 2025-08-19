#include "includes/minishell.h"

void	ft_env(t_env *head, char **args, t_mini_sh *sh)
{
	if (args[1])
	{
		ft_put_error("env: No such file or directory", args[1]);
		sh->last_status = 127;
		return ;
	}
	while (head)
	{
		if (head->value)
		{
			write(STDOUT_FILENO, head->name, ft_strlen(head->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, head->value, ft_strlen(head->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		head = head->next;
	}
	sh->last_status = 0;
}
