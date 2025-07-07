/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:34 by israetor          #+#    #+#             */
/*   Updated: 2025/03/31 19:28:23 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_hex(unsigned int n, int *len, int f)
{
	int					i;
	int					aux;
	char				hex[10];

	i = 0;
	if (n == 0)
	{
		put_char('0', len);
		return (*len);
	}
	while (n != 0)
	{
		aux = n % 16;
		if (aux < 10)
			hex[i++] = aux + '0';
		else
			hex[i++] = aux - 10 + f;
		n = n / 16;
	}
	while (i--)
		put_char(hex[i], len);
	if (*len == -1)
		return (-1);
	return (*len);
}

int	put_hex_p_format(unsigned long n, int *len, int f)
{
	int					i;
	int					aux;
	char				hex[50];

	i = 0;
	if (n == 0)
		put_char('0', len);
	while (n != 0)
	{
		aux = n % 16;
		if (aux < 10)
			hex[i++] = aux + '0';
		else
			hex[i++] = aux - 10 + f;
		n = n / 16;
	}
	while (i--)
		put_char(hex[i], len);
	if (*len == -1)
		return (-1);
	return (*len);
}
