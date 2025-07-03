/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 07:18:29 by ysarac            #+#    #+#             */
/*   Updated: 2024/04/29 23:55:34 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	i;

	src_length = 0;
	while (src[src_length] != '\0')
		src_length++;
	if (dstsize == 0)
	{
		return (src_length);
	}
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_length);
}

static char	**free_all(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	**fill_result(char **res, char const *s, char c, int wc)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (wc--)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		res[j] = (char *)malloc(i - start + 1);
		if (!res[j])
			return (free_all(res, j - 1));
		ft_strlcpy(res[j++], s + start, i - start + 1);
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wc;

	wc = count_words(s, c);
	result = malloc((wc + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	return (fill_result(result, s, c, wc));
}
