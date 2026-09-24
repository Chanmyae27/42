/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:14:22 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/05 20:16:56 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	size_t	i;
	int		word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word++;
		i++;
	}
	return (word);
}

static char	**ft_free(char **words, size_t j)
{
	while (j > 0)
	{
		j--;
		free(words[j]);
	}
	free(words);
	return (NULL);
}

static char	**ft_fill(char **words, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] != '\0' && s[i + len] != c)
				len++;
			words[j] = ft_substr(s, i, len);
			if (!words[j])
				return (ft_free(words, j));
			j++;
			i += len;
		}
		else
			i++;
	}
	words[j] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	words = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!words)
		return (NULL);
	return (ft_fill(words, s, c));
}
