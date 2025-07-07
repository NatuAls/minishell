/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putcharv(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	ft_putnbr_fd(int n, int fd)
{
	int	minn;

	minn = -2147483648;
	if (n == minn)
	{
		putcharv('-', fd);
		putcharv('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		putcharv('-', fd);
		n = -n;
	}
	if (n <= 9)
	{
		n = n + '0';
		putcharv(n, fd);
		return ;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putnbr_fd(n % 10, fd);
}
