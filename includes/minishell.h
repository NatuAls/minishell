#ifndef MINISHELL_H
#	define MINISHELL_H


#	include <errno.h>
#	include <readline/readline.h>
#	include <readline/history.h>
#	include <sys/wait.h>
#	include <signal.h>
#	include "../libft/libft.h"

typedef enum 
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,    //>
	TOKEN_REDIR_IN,     //<
	TOKEN_REDIR_APPEND, //>>
	TOKEN_HEREDOC,      //<<
	TOKEN_EOF
}	TokenType;

typedef struct s_token
{
	TokenType	type;
	char		*value;
	struct s_token	*next;
}	Token;

typedef enum
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}	NodeType;

typedef struct s_ast
{
	NodeType	type;
	char		**args;
	char		*filename;
	TokenType	redir_type;
	int		heredoc_fd;
	struct s_ast	*right;
	struct s_ast	*left;
}	ASTNode;

typedef struct s_mini_sh
{
	int			input;
	pid_t			mypid;
	int			myfd;
//	int			status;
	char 			**envi;

}	t_mini_sh;


void	ft_getinput(t_mini_sh *sh);
Token	*tokenizer(char	*line);
ASTNode	*parse(Token **tokens);
ASTNode	*ft_apply_redirection(ASTNode *node);
void	expand_heredocs(ASTNode *node);
void	ft_excecute(ASTNode *node, t_mini_sh *sh);

void	ft_freeAST(ASTNode *head);
void	ft_free_tokens(Token *tokens);
void	ft_free_strs(char **strs);

void	ft_put_error(char *prefix, char *msg);

void	print_ast(ASTNode *node, int level);

void ft_execute_pipe(ASTNode *node, t_mini_sh *sh);

#	define NRM  "\x1B[0m"
#	define RED  "\x1B[31m"
#	define GRN  "\x1B[32m"
#	define YEL  "\x1B[33m"
#	define BLU  "\x1B[34m"
#	define MAG  "\x1B[35m"
#	define CYN  "\x1B[36m"
#	define WHT  "\x1B[37m"

#endif
