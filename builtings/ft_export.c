#include "includes/minishell.h"

void	ft_sort_env(char **env_arr)
{
	int	i;
	int	swapped;
	int	len;
	char	*tmp;

	do
	{
		swapped = 0;
		i = 0;
		while (env_arr[i + 1])
		{
			len = ft_strlen(env_arr[i]) + 1;
			if (ft_strncmp(env_arr[i], env_arr[i + 1], len) > 0)
			{
				tmp = env_arr[i];
				env_arr[i] = env_arr[i + 1];
				env_arr[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
	while (swapped);
}

void	ft_put_export(t_env *head)
{
	char	**env_arr;
	char	*eq;
	int	i;

	env_arr = ft_env_to_arr(head);
	ft_sort_env(env_arr);
	i = 0;
	while (env_arr[i])
	{
		eq = ft_strchr(env_arr[i], '=');
		write(STDOUT_FILENO, "declare -x ", 11);
		if (eq)
		{
			write(STDOUT_FILENO, env_arr[i], eq - env_arr[i]);
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, eq + 1, ft_strlen(eq + 1));
			write(STDOUT_FILENO, "\"", 1);
		}
		else
			write(STDOUT_FILENO, env_arr[i], ft_strlen(env_arr[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	ft_free_strs(env_arr);
}

int	ft_is_valid_name(char *name)
{
	int i = 0;

	if (!name || !name[0])
		return (0);
	if (ft_isalpha(name[i]) || name[i] == '_')
		i++;
	else
	{
		ft_put_error("export", "the name is not valid");
		return (0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_put_error("export", "the name is not valid");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_process(t_env *head, char *var)
{
	char	**key_value;

	key_value = ft_split(var, '=');
	if (!ft_is_valid_name(key_value[0]))
		return (ft_free_strs(key_value), 1);
	while (head)
	{
		if (!ft_strncmp(head->name, key_value[0], ft_strlen(head->name) + 1))
		{
			if (key_value[1])
			{
				free(head->value);
				head->value = ft_strdup(key_value[1]);
			}
			ft_free_strs(key_value);
			return (0);
		}
		if (head->next == NULL)
			break ;
		head = head->next;
	}
	head->next = ft_new_env(key_value[0], key_value[1]);
	ft_free_strs(key_value);
	return (0);
}

void	ft_export(t_env *head, char *var, t_mini_sh *sh)
{
	if (!var)
	{
		ft_put_export(head);
		sh->last_status = 0;
		return ;
	}
	sh->last_status = ft_export_process(head, var);
}
