/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:48:12 by nalesso           #+#    #+#             */
/*   Updated: 2025/07/22 16:19:50 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void ft_getinput(t_mini_sh*sh)
{
	char	*input;
	Token	*tokens;
	Token	*tokcpy;
	ASTNode	*node;
	ASTNode	*head;
	//char 	**args;

	node = NULL;
	while (1)
	{
		input = readline(GRN "Minishell$>☠ " NRM);
		if (!input)
			perror("input error");
		if (input[0] == ' ' || input[0] =='\0')
		{
			free(input);
			ft_printf("");
			continue ;
		}
		add_history(input);
		ft_printf("Has escrito " BLU "%s\n" NRM,input);
		

		tokens = tokenizer(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		tokcpy = tokens;
		while (tokcpy)
		{
			printf("TOKEN %d: %s\n", tokcpy->type, tokcpy->value);
			tokcpy = tokcpy->next;
		}

		if (!ft_strncmp(tokens->value, "exit", 4))
		{
			ft_free_tokens(tokens);
			if (node)
				ft_freeAST(node);
			free(input);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}

		tokcpy = tokens;
		node = parse(&tokens);
		if (!node)
		{
			ft_free_tokens(tokcpy);
			free(input);
			continue ;
		}
		print_ast(node, 0);
		head = node;
		if (node->type == NODE_PIPE)
			node = node->left;
		ft_excecute(node, sh);
		//printf("*-*" BLU "%s" NRM "*-*\n",node->args[0]);
		//if(node->args[0][0] == '/')   para otras opciones
		ft_free_tokens(tokcpy);
		ft_freeAST(head);
		node = NULL;
		free(input);
	}

}

int	main(int argc, char**argv,char **env)
{
	t_mini_sh shell;	
	
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		shell.mypid = getpid();
		shell.input = 0;
		shell.myfd = 1;	
		shell.envi = env;
		ft_getinput(&shell);
	}

	return (1);
}
