#include "includes/minishell.h"

void	child_heredoc(int *fd, char *delimiter)
{
	char *line;

	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	ft_handle_heredoc(char *filename)
{
	int	pid;
	int	fd[2];
	int	status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_heredoc(fd, filename);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
	}
	return (fd[0]);
}

void	expand_heredocs(t_ast *node)
{
	if (!node)
		return ;
	if (node->redir_type == TOKEN_HEREDOC)
		node->heredoc_fd = ft_handle_heredoc(node->filename);
	expand_heredocs(node->left);
	expand_heredocs(node->right);
}

int	ft_apply_redirection(t_ast *node)
{
	int	fd;

	fd = -1;
	if (node->redir_type == TOKEN_REDIR_OUT)
		fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->redir_type == TOKEN_REDIR_IN)
		fd = open(node->filename, O_RDONLY);
	else if (node->redir_type == TOKEN_REDIR_APPEND)
		fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->redir_type == TOKEN_HEREDOC)
		fd = node->heredoc_fd;
	if (fd < 0)
	{
		ft_put_error(node->filename, strerror(errno));
		return (0);
	}
	if (node->redir_type == TOKEN_REDIR_OUT || node->redir_type == TOKEN_REDIR_APPEND)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	apply_all_redirs(t_ast *node)
{
	if (!node)
		return (1);
	if (node->type == NODE_REDIR)
	{
		if (!apply_all_redirs(node->left))
			return (0);
		return (ft_apply_redirection(node));
	}
	return (1);
}

t_ast	*apply_redirs_and_get_cmd(t_ast *node)
{
	if (!apply_all_redirs(node))
		return (NULL);
	while (node && node->type == NODE_REDIR)
		node = node->left;
	return (node);
}
