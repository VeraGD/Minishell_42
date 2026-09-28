/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:28:39 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:28:43 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split != 0)
	{
		while (split && split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

static void	free_cmd(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->path)
			free(current->path);
		if (current->argv)
			free_split(current->argv);
		if (current->infile)
			free_split(current->infile);
		if (current->outfile)
			free_split(current->outfile);
		if (current->here_doc)
			free_split(current->here_doc);
		free(current);
		current = next;
	}
}

static void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	reset_up(t_shell *shelly)
{
	if (shelly->cmd_tree)
	{
		free_cmd(shelly->cmd_tree);
		shelly->cmd_tree = NULL;
	}
	if (shelly->tokens)
	{
		free_tokens(shelly->tokens);
		shelly->tokens = NULL;
	}
	free_env_var(shelly);
	if (shelly->pids)
	{
		free(shelly->pids);
		shelly->pids = NULL;
	}
}

void	free_env_var(t_shell *shelly)
{
	if (shelly->env_var)
	{
		free(shelly->env_var);
		shelly->env_var = NULL;
	}
}
