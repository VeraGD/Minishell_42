/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:27:53 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:27:55 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_builtin_esp(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
if ((status & 0x7F) == 0) -> finish with exit()
in "else" finish by signal
*/
static int	choose_aux_wait(t_shell *shelly)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_pipex(shelly))
	{
		waitpid(shelly->pids[i], &status, 0);
		if (i == num_pipex(shelly) - 1)
		{
			if ((status & 0x7F) == 0)
				shelly->last_exit = (status >> 8) & 0xFF;
			else
				shelly->last_exit = 128 + (status & 0x7F);
		}
		i++;
	}
	return (0);
}

static int	choose_aux_close(t_shell *shelly, int fd_prev)
{
	if (fd_prev != -1)
		close(fd_prev);
	close(shelly->fd[1]);
	fd_prev = shelly->fd[0];
	return (fd_prev);
}

static void	divide_fork(t_shell *shelly, t_cmd *cmd, int fd_prev, int i)
{
	if (i == 0)
		first_fork_b(shelly, cmd);
	else if (i == num_pipex(shelly) - 1)
		last_fork(shelly, cmd, fd_prev);
	else
		middle_fork(shelly, cmd, fd_prev);
}

int	choose_fork(t_shell *shelly, int child, int fd_prev)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = shelly->cmd_tree;
	while (current)
	{
		if (is_builtin_esp(current->argv[0]) == 1 && !current->next && i == 0)
			check_builtin_in_fork(shelly, current->argv);
		else
		{
			child = 1;
			choose_fork_aux(shelly, i);
			if (shelly->pids[i] == 0)
				divide_fork(shelly, current, fd_prev, i);
			fd_prev = choose_aux_close(shelly, fd_prev);
		}
		i++;
		current = current->next;
	}
	if (child == 1)
		return (choose_aux_wait(shelly));
	return (0);
}
