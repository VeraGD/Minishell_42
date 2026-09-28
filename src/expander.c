/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:02:09 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:02:12 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_line(char *input, t_shell *shelly, int in_squote, int in_dquote)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == SQUOTE && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == DQUOTE && !in_squote)
			in_dquote = !in_dquote;
		else if (input[i] == '$' && !in_squote && ft_strlen(input) > 1)
		{
			result = append_variable(result, input, &i, shelly);
			continue ;
		}
		else
			result = append_char(result, input[i]);
		i++;
	}
	return (result);
}

static int	is_valid_var_char(char c, int pos)
{
	if (pos == 0)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static char	*extract_var_name(char *str, int *i, int pos)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	if (str[start] == '?')
	{
		(*i)++;
		return (ft_strdup("$?"));
	}
	while (str[*i] && is_valid_var_char(str[*i], pos))
	{
		(*i)++;
		pos++;
	}
	len = *i - start;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	pos = 0;
	while (start < *i)
		var_name[pos++] = str[start++];
	var_name[pos] = '\0';
	return (var_name);
}

char	*expand_var(char *str, int *i, t_shell *shelly)
{
	char	*var_name;

	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shelly->last_exit));
	}
	var_name = extract_var_name(str, i, 0);
	search_env_var(shelly, var_name, NULL, 0);
	if (shelly->env_var)
		return (ft_strdup(shelly->env_var));
	return (ft_strdup(""));
}
