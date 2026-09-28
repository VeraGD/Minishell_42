/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:15:19 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/15 15:15:22 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*append_variable(char *result, char *input, int *i, t_shell *shelly)
{
	char	*tmp;
	char	*var;

	var = expand_var(input, i, shelly);
	tmp = result;
	result = ft_strjoin(tmp, var);
	free(tmp);
	return (result);
}

char	*append_char(char *result, char c)
{
	char	*tmp;

	tmp = result;
	result = ft_strjoin_char(tmp, c);
	free (tmp);
	return (result);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
