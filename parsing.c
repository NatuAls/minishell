#include "includes/minishell.h"

int	count_words(Token *tokens)
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

ASTNode	*new_ASTNode(NodeType type, char **args, char *filename, TokenType redir_type)
{
	ASTNode	*new;

	new = malloc(sizeof(ASTNode));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = args;
	new->filename = filename;
	new->redir_type = redir_type;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

ASTNode	*parse_command(Token **tokens)
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

ASTNode *parse_redir(Token **tokens, ASTNode *left)
{
	ASTNode	*redir;
	char 	*filename;
	TokenType	redir_type;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		perror("minishell: syntax error near redirection");
		return (NULL);
	}
	filename = ft_strdup((*tokens)->value);
	redir = new_ASTNode(NODE_REDIR, NULL, filename, redir_type);
	redir->left = left;
	*tokens = (*tokens)->next;
	return (redir);
}

int	is_redir(TokenType type)
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

ASTNode	*parse(Token **tokens)
{
	ASTNode *left;
	ASTNode	*pipe;

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
			return (NULL);
		return (pipe);
	}
	return (left);
}
