/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*p;
	int				i;
	unsigned char	t;

	t = (char)c;
	p = (char *)s;
	i = ft_strlen(s);
	if (!p)
		return (NULL);
	if (t == '\0')
		return (p + i);
	while (i != (-1))
	{
		if (p[i] == t)
		{
			return (p + i);
		}
		i--;
	}
	return (NULL);
}
