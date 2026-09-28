/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:15:50 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/15 16:15:51 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_builtin_in_fork(t_shell *shelly, char **argv)
{
	if (ft_strcmp(argv[0], "exit") == 0)
		builtin_exit(shelly, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		builtin_cd(shelly, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		builtin_export(argv, shelly, 0, 0);
	else if (ft_strcmp(argv[0], "unset") == 0)
		builtin_unset(shelly, argv, 0);
}

void	choose_fork_aux(t_shell *shelly, int i)
{
	if (pipe(shelly->fd) == -1)
		ft_error(shelly, "Error creating pipe", 1, 0);
	shelly->pids[i] = fork();
	if (shelly->pids[i] == -1)
		ft_error(shelly, "Error creating pipe", 1, 0);
}
