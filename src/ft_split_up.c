/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:01:21 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:01:23 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_quotes(const char *s, int i, char quote)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static int	word_count(const char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
			count++;
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i, s[i]);
		else
			while (s[i] && s[i] != ' ')
				i++;
	}
	return (count);
}

static char	*fill_words(t_shell *shelly, const char *s, int *index)
{
	int		start;
	int		len;
	char	*word;

	while (s[*index] == ' ')
		(*index)++;
	start = *index;
	if (s[*index] == '"' || s[*index] == '\'')
		*index = skip_quotes(s, *index, s[*index]);
	else
		while (s[*index] && s[*index] != ' ')
			(*index)++;
	len = *index - start;
	word = malloc(len + 1);
	if (!word)
	{
		ft_error(shelly, "malloc error", 1, 0);
		return (NULL);
	}
	ft_strlcpy(word, &s[start], len + 1);
	return (word);
}

static char	**free_str(char **str, int count)
{
	while (count >= 0)
	{
		free(str[count]);
		count--;
	}
	free(str);
	return (NULL);
}

char	**ft_split_up(t_shell *shelly, const char *s)
{
	char	**result;
	int		words;
	int		i;
	int		index;

	if (!s)
		return (NULL);
	words = word_count(s);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
	{
		ft_error(shelly, "malloc error", 1, 0);
		return (NULL);
	}
	i = 0;
	index = 0;
	while (i < words)
	{
		result[i] = fill_words(shelly, s, &index);
		if (!result[i])
			return (free_str(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}
