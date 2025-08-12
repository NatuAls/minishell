#include "includes/minishell.h"

void	ft_env(t_env *head)
{
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
}
