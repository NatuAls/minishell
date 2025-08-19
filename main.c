/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:48:12 by nalesso           #+#    #+#             */
/*   Updated: 2025/08/12 17:51:00 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"



/*char	*ft_get_prompt()
{
	char	cwd[PATH_MAX];
	char	*tmp1;
	char	*tmp2;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)))
	{
		tmp1 = ft_strjoin(GRN, cwd);
		tmp2 = ft_strjoin(tmp1, " Minishell$>☠ ");
		free(tmp1);
		prompt = ft_strjoin(tmp2, NRM);
		free(tmp2);
		return (prompt);
	}
	tmp1 = ft_strjoin(GRN, "Minishell$>☠ ");
	prompt = ft_strjoin(tmp1, NRM);
	free(tmp1);
	return (prompt);
}*/

void ft_getinput(t_mini_sh*sh)
{
	//char	*prompt;
	char	*input;
	//char 	**args;

	while (1)
	{
		//prompt = ft_get_prompt();
		input = readline(GRN "Minishell☠$> " NRM);
		if(g_signal_vol == SIGINT)
			g_signal_vol = 0; // Reset signal after handling
		else if (g_signal_vol == SIGQUIT)
			g_signal_vol = 0;
		if (!input) // Ctrl+D  hace que readline retorne NULL
		{
			printf("exit\n");
			ft_free_mini_sh(sh, 1);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		if (input[0] == ' ' || input[0] == '\0')
		{
			free(input);
	//		ft_printf("");
			rl_on_new_line(); //mueve el cursor a una nueva linea
    			rl_replace_line("", 0);  //borra el texto de la linea actual
    			rl_redisplay(); //redibuja la linea actual
			continue ;
		}
		add_history(input);
		
		//ft_printf("Has escrito " BLU "%s\n" NRM,input);//para debug
		sh->tokens = tokenizer(input, sh);
		if (!sh->tokens)
		{
			//free(prompt);
			free(input);
			continue ;
		}
		sh->tokens_head = sh->tokens;
		while (sh->tokens)
		{
			printf("TOKEN %d: %s\n", sh->tokens->type, sh->tokens->value);//para debug
			sh->tokens = sh->tokens->next;
		}
		sh->tokens = sh->tokens_head;
		if (!ft_strncmp(sh->tokens->value, "exit", 5))// Comando para salir del shell
		{
			ft_free_mini_sh(sh, 1);
			//free(prompt);
			free(input);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}

		sh->node = parse(&sh->tokens);
		if (!sh->node)
		{
			ft_free_mini_sh(sh, 0);
			//free(prompt);
			free(input);
			continue ;
		}
		sh->node_head = sh->node;
		//print_ast(node, 0);
		expand_heredocs(sh->node);
		if (sh->node->type == NODE_PIPE)
		{	//node = node->left;
			ft_execute_pipe(sh->node, sh);
		}
		else
			ft_execute(sh->node, sh);
		//printf("*-*" BLU "%s" NRM "*-*\n",node->args[0]);
		//if(node->args[0][0] == '/')   para otras opciones
		ft_free_mini_sh(sh, 0);
		//free(prompt);
		free(input);
	}

}

int	main(int argc, char**argv, char **envp)
{
	t_mini_sh	shell;

	(void)argv;
	if (argc == 1)
	{
		shell.mypid = getpid();
		shell.input = 0;
		shell.myfd = 1;	
		shell.env = ft_setenv(envp);
		shell.last_status = 0;
		shell.tokens = NULL;
		shell.tokens_head = NULL;
		shell.node = NULL;
		shell.node_head = NULL;
	 							
		ft_setup_signals();
		ft_getinput(&shell);
	}
//echo hola mundo | tr a-z A-Z | rev  test comando de ejemplo
	return (1);
}
