/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:50:50 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *ha, const char *ne, size_t len)
{
	size_t	i;
	size_t	j;
	char	*haystack;
	char	*needle;

	haystack = (char *)ha;
	needle = (char *)ne;
	i = 0;
	if (!haystack && !needle)
		return (NULL);
	if (len <= 0 || !needle[0])
		return (haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] && needle[j] && i + j < len
			&& needle[j] == haystack[i + j])
			j++;
		if (needle[j] == '\0')
			return (haystack + i);
		i++;
	}
	return (NULL);
}
