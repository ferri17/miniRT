/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:22:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/06 23:45:45 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	word_count(char const *s, char c)
{
	unsigned int	words;

	words = 0;
	if (*s != c && *s != '\0')
		words++;
	while (*s)
	{
		if (*s == c)
		{
			while (*s == c)
				s++;
			if (*s != '\0')
				words++;
			else
				break ;
		}
		s++;
	}
	return (words);
}

static char	*split_words(char const **str, char c)
{
	char			*word;
	unsigned int	i;
	size_t			word_len;

	while (**str == c)
		*str = *str + 1;
	word_len = 0;
	while (str[0][word_len] != c && str[0][word_len] != '\0')
		word_len++;
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i++] = **str;
		*str = *str + 1;
	}
	word[i] = '\0';
	return (word);
}

static void	free_malloc(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	words;
	unsigned int	i;

	words = word_count(s, c);
	arr = (char **)ft_calloc(sizeof(char *), (words + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		arr[i] = split_words(&s, c);
		if (arr[i] == NULL)
		{
			free_malloc(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
