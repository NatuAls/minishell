/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	k;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	k = len;
	if (!d && !s)
		return (0);
	if (len == 0)
		return (dst);
	if (dst < src)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		while (k--)
			d[k] = s[k];
	}
	return (dst);
}
