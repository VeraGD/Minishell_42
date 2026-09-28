/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:28:17 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:28:19 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	aux_fork(t_shell *shelly)
{
	dup2(shelly->fd[1], STDOUT_FILENO);
	close(shelly->fd[0]);
	close(shelly->fd[1]);
}

static void	check_builtin(t_shell *shelly, t_cmd *cmd)
{
	if (is_builtin(cmd->argv[0]) != 0)
	{
		if (ft_strcmp(cmd->argv[0], "valgrind") == 0)
			execute_builtin(cmd, shelly, cmd->argv[1]);
		else
			execute_builtin(cmd, shelly, cmd->argv[0]);
		exit(0);
	}
	else if (ft_strcmp(cmd->argv[0], "./minishell") == 0)
	{
		update_shlvl(shelly);
		execve (cmd->path, cmd->argv, shelly->env);
		ft_error(shelly, "Error running execve", 1, 0);
	}
	else if (ft_strcmp(cmd->argv[0], "valgrind") == 0)
	{
		execve (cmd->path, cmd->argv, shelly->env);
		ft_error(shelly, "Error running execve", 1, 0);
	}
	else
	{
		shelly->last_exit = 0;
		execve (cmd->path, cmd->argv, shelly->env);
		ft_error(shelly, "Error running execve", 1, 0);
	}
}

void	first_fork_b(t_shell *shelly, t_cmd *cmd)
{
	if (cmd->fd_inf != -1)
	{
		dup2(cmd->fd_inf, STDIN_FILENO);
		close(cmd->fd_inf);
	}
	if (num_pipex(shelly) != 1)
	{
		if (cmd->fd_out != -1)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		else
			aux_fork(shelly);
	}
	else
	{
		if (cmd->fd_out != -1)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
	}
	check_builtin(shelly, cmd);
}

void	middle_fork(t_shell *shelly, t_cmd *cmd, int fd_prev)
{
	if (cmd->fd_inf != -1)
	{
		dup2(cmd->fd_inf, STDIN_FILENO);
		close(cmd->fd_inf);
	}
	else
	{
		dup2(fd_prev, STDIN_FILENO);
		close(fd_prev);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else
		aux_fork(shelly);
	check_builtin(shelly, cmd);
}

void	last_fork(t_shell *shelly, t_cmd *cmd, int fd_prev)
{
	(void)shelly;
	if (cmd->fd_inf != -1)
	{
		dup2(cmd->fd_inf, STDIN_FILENO);
		close(cmd->fd_inf);
	}
	else
	{
		dup2(fd_prev, STDIN_FILENO);
		close(fd_prev);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	check_builtin(shelly, cmd);
}
