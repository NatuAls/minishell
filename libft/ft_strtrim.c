/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/02/11 20:54:59 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_para(char const *s1, char const *set)
{
	if (!s1 || !set)
		return (0);
	else
		return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	i;
	unsigned int	z;

	if (!check_para(s1, set))
		return (NULL);
	z = ft_strlen(s1);
	i = 0;
	if (z == 0)
		return (ft_strdup(""));
	z--;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (z > i && ft_strchr(set, s1[z]))
		z--;
	if (i > z)
		return (ft_strdup(""));
	str = ft_substr(s1, i, z - i + 1);
	return (str);
}
/*
#include <stdio.h>
int main()
{
	char *s = ft_strtrim("abbabababa", "ab");
	printf("%s\n",s);
	free(s);
	return 0;
}*/
