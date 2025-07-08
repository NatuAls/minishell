#include "includes/minishell.h"

Token	*new_token(TokenType type, char	*value)
{
	Token	*new;

	new = malloc(sizeof(Token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	handle_quotes(char *line, int *i, Token **head, Token **last)
{
	char	*word;
	char	*tmp;
	char	c[2];
	Token	*tok;

	word = ft_strdup("");
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		c[0] = line[*i];
		c[1] = '\0';
		tmp = word;
		word = ft_strjoin(word, c);
		free(tmp);
		(*i)++;
	}
	if (line[*i] == '"')
		(*i)++;
	tok = new_token(TOKEN_WORD, word);
	if (!*head)
		*head = tok;
	else
		(*last)->next = tok;
	*last = tok;
}

void	handle_pipe(int *i, Token **head, Token **last)
{
	Token	*tok;

	tok = new_token(TOKEN_PIPE, "|");
	if (!*head)
		*head = tok;
	else
		(*last)->next = tok;
	*last = tok;
	(*i)++;
}

//void	handle_redirection(char *line, int *i, Token **head, Token **last)

void	handle_word(char *line, int *i, Token **head, Token **last)
{
	char	*word;
	char	*tmp;
	char	c[2];
	Token	*tok;

	word = ft_strdup("");
	while (line[*i] && line[*i] != ' ')
	{
		c[0] = line[*i];
		c[1] = '\0';
		tmp = word;
		word = ft_strjoin(word, c);
		free(tmp);
		(*i)++;
	}
	tok = new_token(TOKEN_WORD, word);
	if (!*head)
		*head = tok;
	else
		(*last)->next = tok;
	*last = tok;
}

Token	*tokenizer(char *line)
{
	int	i;
	Token	*head;
	Token	*last;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		if (line[i] == '"')
			handle_quotes(line, &i, &head, &last);
		else if (line[i] == '|')
			handle_pipe(&i, &head, &last);
		//else if (line[i] == '>' || line[i] == '<')
		//	handle_redirection(line, &i, &head, &last);
		else if (line[i] == ' ')
			i++;
		else
			handle_word(line, &i, &head, &last);
	}
	return (head);
}
