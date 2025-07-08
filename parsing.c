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

ASTNode	*new_ASTNode(NodeType type, char **args)
{
	ASTNode	*new;

	new = malloc(sizeof(ASTNode));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = args;
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
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (i < size && *tokens && (*tokens)->type == TOKEN_WORD)
	{
		args[i] = (*tokens)->value;
		*tokens = (*tokens)->next;
		i++;
	}
	args[i] = NULL;
	return (new_ASTNode(NODE_COMMAND, args));
}
