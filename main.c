#include "includes/minishell.h"

void	ft_excecute(ASTNode*command, t_mini_sh*sh)
{
	int	status;
	char *path;

	status = 0;
	path = ft_strdup("/bin/");
	path = ft_strjoin(path, command->args[0]);

	sh->mypid = fork();
	if (sh->mypid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (sh->mypid == 0)
	{
			if (execve(path, command->args, NULL) == -1)
			{
				printf("%s: command not found\n",command->args[0]);
				free(path);
				exit(EXIT_FAILURE);
			}
	}
	else
		waitpid(sh->mypid, &status, 0);
}


void ft_getinput(t_mini_sh*sh)
{
	char	*input;

	(void)sh;	
	while (1)
	{
		input = readline(GRN "Minishell$> " NRM);
		if (!input)
			perror("input error");
		if (input[0] == ' ' || input[0] =='\0')
		{
			free(input);
			ft_printf("");
		}
		else 
		{
			add_history(input);
			ft_printf("Has escrito " BLU "%s\n" NRM,input);
		

			Token *tokens = tokenizer(input);
			Token *tokcpy = tokens;
			while (tokcpy)
			{
				printf("TOKEN %d: %s\n", tokcpy->type, tokcpy->value);
				tokcpy = tokcpy->next;
			}

			ASTNode *node = parse_command(&tokens);
			printf("ASTNode %d: ", node->type);
			char **args = node->args;
			printf("{ ");
			while(args && *args)
			{
				printf("'%s' ", *args);
				args++;
			}
			printf("}\n");

			ft_excecute(node, sh);
		}
	}


}

//int	main(int argc, char**argv,char **env)
int	main(void)
{
	t_mini_sh shell;	

	shell.mypid = getpid();
	shell.input = 0;
	shell.myfd = 1;	
	ft_getinput(&shell);

}
