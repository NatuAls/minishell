/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:52 by nalesso           #+#    #+#             */
/*   Updated: 2025/08/26 16:37:06 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include "../libft/libft.h"

extern volatile sig_atomic_t	g_signal_vol;

typedef enum s_token_type
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum s_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	char			*filename;
	t_token_type	redir_type;
	int				heredoc_fd;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini_sh
{
	char	*input;
	pid_t	mypid;
	int		myfd;
	t_env	*env;
	int		last_status;
	t_token	*tokens;
	t_token	*tokens_head;
	t_ast	*node;
	t_ast	*node_head;
}	t_mini_sh;

void	ft_getinput(t_mini_sh *sh);
t_token	*tokenizer(char	*line, t_mini_sh *sh);
t_ast	*parse(t_token **tokens);
t_ast	*ft_apply_redirection(t_ast *node);
void	expand_heredocs(t_ast *node);
void	ft_execute(t_ast *node, t_mini_sh *sh);

void	ft_freeAST(t_ast *head);
void	ft_free_tokens(t_token *tokens);
void	ft_free_env(t_env *head);
void	ft_free_strs(char **strs);
void	ft_free_mini_sh(t_mini_sh *sh, int env);

void	ft_put_error(char *prefix, char *msg);

void	print_ast(t_ast *node, int level);

void	ft_execute_pipe(t_ast *node, t_mini_sh *sh);

int		ft_execute_builting(t_ast *node, t_mini_sh *sh);

void	handle_status(int status, t_mini_sh *sh);

void	ft_echo(char **args, t_mini_sh *sh);
void	ft_cd(char **args, t_mini_sh *sh);
void	ft_pwd(t_mini_sh *sh);
void	ft_export(t_env *head, char *var, t_mini_sh *sh);
void	ft_unset(t_env **head, char **vars, t_mini_sh *sh);
void	ft_sort_env(char **env_arr);
void	ft_env(t_env *head, char **args, t_mini_sh *sh);
void	ft_bexit(t_mini_sh *sh);

t_env	*ft_new_env(char *name, char *value);
t_env	*ft_setenv(char **env);
t_env	*ft_getenv(t_env *head, char *name);
char	**ft_env_to_arr(t_env *head);

void	handle_sig_c(int sig);
void	ft_setup_signals();
void	ft_setup_own();

# define NRM "\001\x1B[0m\002"
# define RED "\001\x1B[31m\002"
# define GRN "\001\x1B[32m\002"
# define YEL "\001\x1B[33m\002"
# define BLU "\001\x1B[34m\002"
# define MAG "\001\x1B[35m\002"
# define CYN "\001\x1B[36m\002"
# define WHT "\001\x1B[37m\002"
#endif
