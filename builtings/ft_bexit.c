/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:50:51 by nalesso           #+#    #+#             */
/*   Updated: 2025/08/26 11:51:18 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_bexit(t_mini_sh *sh)
{
	int	exit_status;

	exit_status = sh->last_status;
	ft_free_mini_sh(sh, 1);
	rl_clear_history();
	exit(exit_status);
}
