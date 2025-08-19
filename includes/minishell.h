#ifndef MINISHELL_H
#	define MINISHELL_H


#	include <errno.h>
#	include <readline/readline.h>
#	include <readline/history.h>
#	include <sys/wait.h>
#	include <signal.h>
#	include <limits.h>
#	include "../libft/libft.h"

extern volatile sig_atomic_t g_signal_vol;

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

typedef struct s_env
{
	char		*name;
	char		*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini_sh
{
	char			*input;
	pid_t			mypid;
	int			myfd;
//	int			status;
	t_env 			*env;
	int			last_status;
	Token			*tokens;
	Token			*tokens_head;
	ASTNode			*node;
	ASTNode			*node_head;

}	t_mini_sh;


void	ft_getinput(t_mini_sh *sh);
Token	*tokenizer(char	*line, t_mini_sh *sh);
ASTNode	*parse(Token **tokens);
ASTNode	*ft_apply_redirection(ASTNode *node);
void	expand_heredocs(ASTNode *node);
void	ft_execute(ASTNode *node, t_mini_sh *sh);

void	ft_freeAST(ASTNode *head);
void	ft_free_tokens(Token *tokens);
void	ft_free_env(t_env *head);
void	ft_free_strs(char **strs);
void	ft_free_mini_sh(t_mini_sh *sh, int env);

void	ft_put_error(char *prefix, char *msg);

void	print_ast(ASTNode *node, int level);

void	ft_execute_pipe(ASTNode *node, t_mini_sh *sh);

int	ft_execute_builting(ASTNode *node, t_mini_sh *sh);

void	ft_echo(char **args, t_mini_sh *sh);
void	ft_cd(char **args, t_mini_sh *sh);
void	ft_pwd(t_mini_sh *sh);
void	ft_export(t_env *head, char *var, t_mini_sh *sh);
void	ft_unset(t_env **head, char **vars, t_mini_sh *sh);
void	ft_env(t_env *head, char **args, t_mini_sh *sh);
void	ft_bexit(t_mini_sh *sh);

t_env	*ft_new_env(char *name, char *value);
t_env	*ft_setenv(char **env);
char	*ft_getenv(t_env *head, char *name);
char	**ft_env_to_arr(t_env *head);

void	handle_sig_c(int sig);
void	ft_setup_signals(void);
void	ft_setup_own();

#define RLNP_S "\001"
#define RLNP_E "\002"
#define NRM RLNP_S "\x1B[0m"  RLNP_E
#define RED RLNP_S "\x1B[31m" RLNP_E
#define GRN RLNP_S "\x1B[32m" RLNP_E
#define YEL RLNP_S "\x1B[33m" RLNP_E
#define BLU RLNP_S "\x1B[34m" RLNP_E
#define MAG RLNP_S "\x1B[35m" RLNP_E
#define CYN RLNP_S "\x1B[36m" RLNP_E
#define	WHT RLNP_S "\x1B[37m" RLNP_E

#endif
