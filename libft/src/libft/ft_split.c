/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:25:55 by eedwards          #+#    #+#             */
/*   Updated: 2024/09/04 14:42:56 by eedwards         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	new_word;
	int	words;

	i = 0;
	new_word = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && new_word == 0)
		{
			words++;
			new_word = 1;
		}
		else if (s[i] == c)
			new_word = 0;
		i++;
	}
	return (words);
}

static void	*ft_free(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
	return (NULL);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**split(char const *s, char c, char **arr, int words)
{
	int				i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		arr[i] = ft_substr(s, j, word_len((s + j), c));
		if (!arr[i])
		{
			ft_free(arr, i);
			return (NULL);
		}
		j += word_len((s + j), c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = split(s, c, arr, words);
	return (arr);
}
