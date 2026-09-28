/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_built.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:29:00 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:29:03 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static char	*get_cmd_path(t_shell *shelly, char *cmd1, size_t i)
{
	char	**split1;
	char	**split2;
	char	*join;
	char	*join_cmd;

	if (is_not_empty_or_spaces(cmd1))
	{
		search_env_var(shelly, "PATH", NULL, i);
		split1 = ft_split(shelly->env_var, ':');
		split2 = ft_split(cmd1, ' ');
		while (i < ft_strlen_double(split1))
		{
			join = ft_strjoin(split1[i], "/");
			join_cmd = ft_strjoin(join, split2[0]);
			if (access(join_cmd, F_OK) == 0)
				return (aux_path(split1, split2, join, join_cmd));
			free(join_cmd);
			free(join);
			i++;
		}
		free_split(split2);
		free_split(split1);
	}
	return (NULL);
}

void	update_shlvl(t_shell *shelly)
{
	int		index;
	int		i;
	char	**env_split;
	char	*new_line;

	i = 0;
	search_env_var(shelly, "SHLVL", NULL, 0);
	while (shelly->env[i] != 0)
	{
		env_split = ft_split(shelly->env[i], '=');
		if (ft_strcmp("SHLVL", env_split[0]) == 0)
		{
			index = i;
			break ;
		}
		free_split(env_split);
		i++;
	}
	shelly->env_var[0] = shelly->env_var[0] + 1;
	new_line = ft_strjoin("SHLVL=", shelly->env_var);
	update_env(shelly, new_line, index, 0);
}

void	aux_check_b_cmd(t_cmd *c, t_shell *s)
{
	while (c)
	{
		if (ft_strcmp(c->argv[0], "./minishell") == 0)
			c->path = ft_strdup(c->argv[0]);
		else if (is_builtin(c->argv[0]) == 0)
		{
			c->path = get_cmd_path(s, c->argv[0], 0);
			if (c->path == NULL)
			{
				if (access(c->argv[0], F_OK) == 0)
					c->path = ft_strdup(c->argv[0]);
				else
				{
					c->fd_out = -2;
					return (ft_error(s, "+: cmd not found", 1, c->argv[0]));
				}
			}
		}
		open_files(s, c);
		create_all_files(s, c);
		c = c->next;
	}
}

void	check_built_comand(t_shell *s)
{
	t_cmd	*c;

	s->pids = (pid_t *)malloc(num_pipex(s) * sizeof(pid_t));
	if (!s->pids)
		return (ft_error(s, "malloc error", 1, 0));
	c = s->cmd_tree;
	aux_check_b_cmd(c, s);
}
