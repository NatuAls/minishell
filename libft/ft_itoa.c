/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenr(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	checkn(int n, int *ps)
{
	int	num;

	num = -1;
	while (n < 0)
	{
		n = n * num ;
		*ps = 1;
	}
	return (n);
}

static int	checkmax(int n, int *max)
{
	if (-2147483648 >= n)
	{
		n = -2147483647;
		*max = 1;
	}
	else if (2147483647 <= n)
	{
		n = 2147483646;
		*max = 1;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		counter;
	int		ps;
	int		max;

	max = 0;
	ps = 0;
	n = checkmax(n, &max);
	n = checkn(n, &ps);
	counter = lenr(n) + 1 + ps;
	str = (char *)malloc(sizeof(*str) * counter);
	if (!str)
		return (NULL);
	if (ps == 1)
		str[0] = '-';
	str[counter - 1] = '\0';
	counter = counter - 2;
	while (n >= 10)
	{
		str[counter--] = '0' + n % 10 + max;
		n = n / 10;
		max = 0;
	}
	str[counter--] = '0' + n;
	return (str);
}
