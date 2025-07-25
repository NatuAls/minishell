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
	char	quote_char;
	Token	*tok;

	word = ft_strdup("");
	quote_char = line[(*i)++];
	while (line[*i] && line[*i] != quote_char)
	{
		c[0] = line[*i];
		c[1] = '\0';
		tmp = word;
		word = ft_strjoin(word, c);
		free(tmp);
		(*i)++;
	}
	if (line[*i] == quote_char)
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

	if (!*head)
	{
		perror("minishell: syntax error near unexpected token '|'");
		exit(258);
	}
	tok = new_token(TOKEN_PIPE, ft_strdup("|"));
	(*last)->next = tok;
	*last = tok;
	(*i)++;
}

void	handle_redirection(char *line, int *i, Token **head, Token **last)
{
	Token	*tok;
	
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tok = new_token(TOKEN_HEREDOC, ft_strdup("<<"));
		(*i)++;
	}
	else if (line[*i] == '<')
		tok = new_token(TOKEN_REDIR_IN, ft_strdup("<"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tok = new_token(TOKEN_REDIR_APPEND, ft_strdup(">>"));
		(*i)++;
	}
	else
		tok = new_token(TOKEN_REDIR_OUT, ft_strdup(">"));
	if (!*head)
		*head = tok;	
	else
		(*last)->next = tok;
	*last = tok;
	(*i)++;
}

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

int	check_quotes(char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '\\' || line[i] == '&')
		{
			if (!in_single && !in_double)
			{
				printf("Character not supported: '%c'\n", line[i]);
				return (2);
			}
		}
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

Token	*tokenizer(char *line)
{
	int	i;
	int	checker;
	Token	*head;
	Token	*last;

	i = 0;
	head = NULL;
	last = NULL;
	checker = check_quotes(line);
	if (checker == 0)
	{
		while (line[i])
		{
			if (line[i] == '"' || line[i] == '\'')
				handle_quotes(line, &i, &head, &last);
			else if (line[i] == '|')
				handle_pipe(&i, &head, &last);
			else if (line[i] == '>' || line[i] == '<')
				handle_redirection(line, &i, &head, &last);
			else if (line[i] == ' ')
				i++;
			else
				handle_word(line, &i, &head, &last);
		}
	}
	else if (checker == 1)
		printf("Unclosed quotes\n");
	return (head);
}
