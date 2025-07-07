/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:05 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:05 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space_b(const char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	s;

	i = 0;
	res = 0;
	s = 1;
	while (space_b(str, i))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}
/*
	while (str[i] != '\0' && str)
	{
		while (space_b(str, i))
			i++;
		if ((str[i] == '+' || str[i] == '-') && res == 0)
		{
			if (str[i] == '-')
				s = -1;
			i++;
		}
		if (!ft_isdigit(str[i]))
			return (res * s);
		else
			res = (res * 10) + (str[i] - '0');
		i++;
	}*/
