/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:29:54 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/21 16:29:59 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(t_shell *shelly, char *str, int num_exit, char *var)
{
	int	i;

	i = 0;
	(void)shelly;
	while (str[i])
	{
		if (str[i] != '+')
			ft_putchar_fd(str[i], 2);
		else
			ft_putstr_fd(var, 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
	shelly->last_exit = num_exit;
}

void	free_shell(t_shell *shelly)
{
	if (shelly->env != NULL)
	{
		free_split(shelly->env);
		shelly->env = NULL;
	}
}
