/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:22:11 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/26 15:22:14 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*parse_normal_text(char *str, int *i, t_shell *shelly)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			temp = expand_var(str, i, shelly);
			result = strjoin_and_free(result, temp);
		}
		else
		{
			temp = ft_strndup(&str[*i], 1);
			result = strjoin_and_free(result, temp);
			(*i)++;
		}
	}
	return (result);
}

static char	*parse_double_quote(char *str, int *i, t_shell *shelly)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1] && (ft_isalnum(str[*i + 1])
				|| str[*i + 1] == '_' || str[*i + 1] == '?'))
		{
			temp = expand_var(str, i, shelly);
			result = strjoin_and_free(result, temp);
		}
		else
		{
			temp = ft_strndup(&str[*i], 1);
			result = strjoin_and_free(result, temp);
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

static char	*parse_single_quote(char *str, int *i)
{
	int		start;
	char	*text;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	text = ft_substr(str, start, *i - start);
	if (str[*i] == '\'')
		(*i)++;
	return (text);
}

char	*parse_expansion(char *input, t_shell *shelly)
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'')
		{
			temp = parse_single_quote(input, &i);
			result = strjoin_and_free(result, temp);
		}
		else if (input[i] == '"')
		{
			temp = parse_double_quote(input, &i, shelly);
			result = strjoin_and_free(result, temp);
		}
		else
		{
			temp = parse_normal_text(input, &i, shelly);
			result = strjoin_and_free(result, temp);
		}
	}
	return (result);
}
