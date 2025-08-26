#include "includes/minishell.h"

int	count_words(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

t_ast	*new_ASTNode(t_node_type type, char **args, char *filename, t_token_type redir_type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = args;
	new->filename = filename;
	new->redir_type = redir_type;
	new->heredoc_fd = -1;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

t_ast	*parse_command(t_token **tokens)
{
	int	i;
	int	size;
	char	**args;

	i = 0;
	size = count_words(*tokens);
	if (!size)
		return (NULL);
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (i < size && *tokens && (*tokens)->type == TOKEN_WORD)
	{
		args[i] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		i++;
	}
	args[i] = NULL;
	return (new_ASTNode(NODE_COMMAND, args, NULL, TOKEN_NONE));
}

t_ast *parse_redir(t_token **tokens, t_ast *left)
{
	t_ast	*redir;
	char 	*filename;
	t_token_type	redir_type;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		printf("minishell: syntax error near redirection\n");
		ft_freeAST(left);
		return (NULL);
	}
	filename = ft_strdup((*tokens)->value);
	redir = new_ASTNode(NODE_REDIR, NULL, filename, redir_type);
	redir->left = left;
	*tokens = (*tokens)->next;
	return (redir);
}

int	is_redir(t_token_type type)
{
	int	result;

	result = 0;
	if (type == TOKEN_REDIR_OUT)
		result = 1;
	else if (type == TOKEN_HEREDOC)
		result = 1;
	else if (type == TOKEN_REDIR_IN)
		result = 1;
	else if (type == TOKEN_REDIR_APPEND)
		result = 1;
	return (result);
}

t_ast	*parse(t_token **tokens)
{
	t_ast *left;
	t_ast	*pipe;

	left = parse_command(tokens);
	while (*tokens && is_redir((*tokens)->type))
	{
		left = parse_redir(tokens, left);
		if (!left)
			return (NULL);
	}
	if (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		pipe = new_ASTNode(NODE_PIPE, NULL, NULL, TOKEN_NONE);
		pipe->left = left;
		pipe->right = parse(tokens);
		if (!pipe->right)
		{
			ft_freeAST(pipe);
			return (NULL);
		}
		return (pipe);
	}
	return (left);
}
