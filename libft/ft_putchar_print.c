/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:47:49 by israetor          #+#    #+#             */
/*   Updated: 2025/03/31 18:47:50 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_char(int c, int *len)
{
	if (*len != -1)
	{
		if ((write(1, &c, 1)) > 0)
			(*len)++;
		else
		{
			*len = -1;
			return ;
		}
	}
}

void	putchar_o(const char *c, unsigned int lenc, int *len)
{
	if (write(1, c, lenc) > 0)
	{
		*len += lenc;
		return ;
	}
	else
	{
		*len = -1;
		return ;
	}
}

int	put_string(char *ap, int *len)
{
	size_t	i;

	i = 0;
	if (ap == NULL)
	{
		putchar_o("(null)", 6, len);
		return (*len);
	}
	while (ap[i] != '\0' && *len != -1)
	{
		put_char(ap[i], len);
		i++;
	}
	return (*len);
}
