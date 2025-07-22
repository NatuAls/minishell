/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:46:16 by nalesso           #+#    #+#             */
/*   Updated: 2025/07/22 16:18:01 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_free_strs(char **strs)
{
	int i = 0;

	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	ft_freeAST(ASTNode *head)
{
	if (!head)
		return ;
	ft_freeAST(head->left);
	ft_freeAST(head->right);
	if (head->args)
		ft_free_strs(head->args);
	if (head->filename)
		free(head->filename);
	free(head);
}

void	ft_free_tokens(Token *tokens)
{
	Token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
