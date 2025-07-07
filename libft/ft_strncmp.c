/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*val1;
	unsigned char	*val2;

	i = 0;
	val1 = (unsigned char *)s1;
	val2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && ((val1[i] != '\0') || (val2[i] != '\0')))
	{
		if (val1[i] != val2[i])
			return (val1[i] - val2[i]);
		i++;
	}
	return (0);
}
