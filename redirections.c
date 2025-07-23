#include "includes/minishell.h"

ASTNode	*ft_apply_redirection(ASTNode *node)
{
	int	fd;

	if (node->redir_type == TOKEN_REDIR_OUT)
		fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->redir_type == TOKEN_REDIR_IN)
		fd = open(node->filename, O_RDONLY);
	else if (node->redir_type == TOKEN_REDIR_APPEND)
		fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", node->filename);
		return (NULL);
	}
	if (node->redir_type == TOKEN_REDIR_OUT || node->redir_type == TOKEN_REDIR_APPEND)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (node->left);
}
