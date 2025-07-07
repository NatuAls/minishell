/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israetor <israetor@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:49:06 by israetor          #+#    #+#             */
/*   Updated: 2025/01/15 19:49:06 by israetor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len_words(char const *s, char c)
{
	unsigned int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static int	num_words(char const *s, char c)
{
	unsigned int	wordlen;
	unsigned int	i;

	i = 0;
	wordlen = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			wordlen++;
		while (s[i] != c && s[i])
			i++;
	}
	return (wordlen);
}

static char	**free_words(char **words)
{
	unsigned int	i;

	i = 0;
	while (words[i] != 0)
	{
		free(words[i]);
		words[i] = 0;
		i++;
	}
	free(words);
	words = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	wlen;
	unsigned int	numw;
	char			**wordsa;

	numw = num_words(s, c);
	wordsa = ft_calloc(sizeof(char *), numw + 1);
	if (!wordsa)
		return (0);
	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			wlen = check_len_words(s, c);
			wordsa[i] = ft_substr(s, 0, wlen);
			if (i <= numw && !wordsa[i++])
				return (free_words(wordsa));
			s += wlen;
		}
	}
	wordsa[i] = 0;
	return (wordsa);
}
