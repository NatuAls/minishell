#include <includes/minishell.h>

void	print_indent(int level)
{
	while (level--)
		printf("  ");
}

void	print_ast(ASTNode *node, int level)
{
	if (!node)
		return;

	print_indent(level);

	if (node->type == NODE_COMMAND)
	{
		printf("[COMMAND]");
		if (node->args)
		{
			printf(" args: ");
			for (int i = 0; node->args[i]; i++)
				printf("'%s' ", node->args[i]);
		}
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		printf("[PIPE]\n");
		print_ast(node->left, level + 1);
		print_ast(node->right, level + 1);
	}
	else if (node->type == NODE_REDIR)
	{
		printf("[REDIR] type: ");
		if (node->redir_type == TOKEN_REDIR_IN)
			printf("<");
		else if (node->redir_type == TOKEN_REDIR_OUT)
			printf(">");
		else if (node->redir_type == TOKEN_REDIR_APPEND)
			printf(">>");
		else if (node->redir_type == TOKEN_HEREDOC)
			printf("<<");
		else
			printf("unknown");
		printf(" file: '%s'\n", node->filename);
		print_ast(node->left, level + 1); // REDIR solo tiene left
	}
}
