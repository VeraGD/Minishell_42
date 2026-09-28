/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:32:34 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/13 15:43:52 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*fill_words(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (0);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_str(char **str, int count)
{
	while (count >= 0)
	{
		free(str[count]);
		count--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		end;
	int		i;
	int		start;
	char	**str;

	str = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	start = 0;
	i = 0;
	while (i < word_count(s, c))
	{
		while (s[start] == c && s[start] != '\0')
			start++;
		end = start;
		while (s[end] != c && s[end] != '\0')
			end++;
		str[i] = fill_words(s, start, end);
		if (!str[i])
			free_str(str, i);
		i++;
		start = end;
	}
	str[i] = NULL;
	return (str);
}
