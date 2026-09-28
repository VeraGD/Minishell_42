/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:30:03 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:30:05 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path_built(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->here_doc[0] != NULL)
			return (0);
		if (current->path == NULL && is_builtin(current->argv[0]) == 0)
			return (1);
		else if (current->fd_inf == -2 || current->fd_out == -2)
			return (1);
		current = current->next;
	}
	return (0);
}

int	setup_pipe(t_shell *shelly)
{
	t_cmd	*current;

	current = shelly->cmd_tree;
	if (check_path_built(current) == 1)
		return (1);
	if (current->here_doc[0] != NULL)
	{
		create_file(current, shelly);
		current->fd_inf = open("tmp.txt", O_RDONLY);
		if (current->fd_inf == -1)
			return (1);
		choose_fork(shelly, 0, -1);
		unlink("tmp.txt");
	}
	else
		choose_fork(shelly, 0, -1);
	return (0);
}
