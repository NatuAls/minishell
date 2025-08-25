#include "includes/minishell.h"

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

t_env	*ft_setenv(char **env)
{
	int	i;
	char	**key_value;
	t_env	*head;
	t_env	*last;
	t_env	*new;

	i = 0;
	head = NULL;
	last = NULL;
	while (env[i])
	{
		key_value = ft_split(env[i], '=');
		new = ft_new_env(key_value[0], key_value[1]);
		ft_free_strs(key_value);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}

t_env	*ft_getenv(t_env *head, char *name)
{
	t_env	*node;

	node = head;
	while (node)
	{
		if (!ft_strncmp(node->name, name, ft_strlen(name) + 1))
			break ;
		node = node->next;
	}
	return (node);
}

int	ft_envlen(t_env *head)
{
	int	i;

	i = 0;
	while(head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	**ft_env_to_arr(t_env *head)
{
	char	**result;
	char	*tmp1;
	int	env_len;
	int	i;

	env_len = ft_envlen(head);
	result = malloc(sizeof(char *) * (env_len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < env_len)
	{
		if (head->value)
		{
			tmp1 = ft_strjoin(head->name, "=");
			result[i] = ft_strjoin(tmp1, head->value);
			free(tmp1);
		}
		else
			result[i] = ft_strdup(head->name);
		i++;
		head = head->next;
	}
	result[i] = NULL;
	return (result);
}
