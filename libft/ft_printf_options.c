/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:05 by israetor          #+#    #+#             */
/*   Updated: 2025/03/31 19:29:01 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_pointer(unsigned long p, int *len)
{
	if (!p)
	{
		putchar_o("(nil)", 5, len);
		return (*len);
	}
	else
	{
		putchar_o("0x", 2, len);
		put_hex_p_format(p, len, 'a');
		return (*len);
	}
}

int	put_nbr(int nb, int *len)
{
	if (*len != -1)
	{
		if (nb == -2147483648)
		{
			putchar_o("-2147483648", 11, len);
			return (*len);
		}
		if (nb < 0)
		{
			put_char('-', len);
			nb = -nb;
		}
		if (nb > 9)
			put_nbr(nb / 10, len);
		put_char(nb % 10 + '0', len);
	}
	return (*len);
}

int	put_uint(unsigned int nb, int *len)
{
	if (*len != -1)
	{
		if (nb > 9)
			put_uint(nb / 10, len);
		put_char(nb % 10 + '0', len);
	}
	return (*len);
}
