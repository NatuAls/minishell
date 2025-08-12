#include "includes/minishell.h"

void	ft_unset(t_env **head, char **vars)
{
	int	i;
	t_env	*prev;
	t_env	*curr;

	i = 1;
	while (vars[i])
	{
		prev = NULL;
		curr = *head;
		while (curr)
		{
			if (!ft_strncmp(curr->name, vars[i], ft_strlen(vars[i]) + 1))
			{
				if (prev)
					prev->next = curr->next;
				else
					*head = (*head)->next;
				free(curr->name);
				free(curr->value);
				free(curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
}
