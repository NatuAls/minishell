/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:44:27 by israetor          #+#    #+#             */
/*   Updated: 2025/04/01 19:09:35 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	int		rvalue;

	va_start(ap, str);
	rvalue = parse_s(str, ap);
	va_end(ap);
	return (rvalue);
}

int	parse_s(const char *str, va_list ap)
{
	int	len;

	len = 0;
	while (*str && len != -1)
	{
		if (*str == '%')
		{
			str++;
			len = check_conv(*str, ap, &len);
		}
		else
		{
			put_char(*str, &len);
		}
		str++;
	}
	if (len == -1)
		return (-1);
	return (len);
}

int	check_conv(const char str, va_list ap, int *len)
{
	if (str == 'c')
		put_char(va_arg(ap, int), len);
	else if (str == 's')
		*len = put_string(va_arg(ap, char *), len);
	else if (str == 'p')
		*len = put_pointer(va_arg(ap, unsigned long), len);
	else if (str == 'd' || str == 'i')
		*len = put_nbr(va_arg(ap, int), len);
	else if (str == 'u')
		*len = put_uint(va_arg(ap, unsigned int), len);
	else if (str == 'x')
		*len = put_hex(va_arg(ap, unsigned int), len, 'a');
	else if (str == 'X')
		*len = put_hex(va_arg(ap, unsigned int), len, 'A');
	else if (str == '%')
		put_char('%', len);
	return (*len);
}
