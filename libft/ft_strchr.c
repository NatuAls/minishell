/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	t;
	unsigned int	k;
	char			*p;

	t = (char)c;
	i = 0;
	p = (char *)s;
	k = ft_strlen(s);
	if (!s)
		return (0);
	if (t == '\0')
		return (p + k);
	while (p[i] != '\0')
	{	
		if (p[i] == t)
		{
			return (p + i);
		}
		i++;
	}
	return (0);
}*/
/*
char	*ft_strchr(const char *str, int c)
{
	
	char	*s;
	int		k;

	k = ft_strlen(str);
	s = (char *)str;
	if (s == 0)
		return (NULL);
	if ((char)c == '\0')
		return (s + k);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (s);
		s++;
	}*/
char	*ft_strchr(const char *str, int c)
{
	char	*s;
	int		k;

	k = ft_strlen(str);
	s = (char *)str;
	if (s == 0)
		return (NULL);
	if ((char)c == '\0')
		return (s + k);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	return (NULL);
}
/*	return (NULL);
}*/
