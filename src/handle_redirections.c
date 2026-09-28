/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:59:51 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/05 15:59:54 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_new_cmd(t_shell *shelly)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		ft_error(shelly, "malloc error", 1, 0);
		return (NULL);
	}
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->outfile = (char **)malloc(5 * sizeof(char *));
	new_cmd->infile = (char **)malloc(5 * sizeof(char *));
	new_cmd->here_doc = (char **)malloc(5 * sizeof(char *));
	if (!new_cmd->outfile || !new_cmd->infile || !new_cmd->here_doc)
	{
		ft_error(shelly, "malloc error", 1, 0);
		return (NULL);
	}
	new_cmd->outfile[0] = NULL;
	new_cmd->infile[0] = NULL;
	new_cmd->here_doc[0] = NULL;
	return (new_cmd);
}

t_cmd	*handle_pipe(t_shell *shelly, t_cmd *current)
{
	if (!current)
	{
		printf("Error: PIPE sin comando previo\n");
		return (NULL);
	}
	current->next = create_new_cmd(shelly);
	return (current->next);
}

static void	aux_handle_redirections(t_token **tmp, t_cmd *current, int *index)
{
	current->here_doc[index[2]] = strdup("1679");
	if ((*tmp)->next && (*tmp)->next->type == ARG)
	{
		*tmp = (*tmp)->next;
		if ((*tmp)->value != NULL)
		{
			free(current->here_doc[index[2]]);
			current->here_doc[index[2]] = strdup((*tmp)->value);
		}
	}
}

static int	*null_index(int *index, t_cmd *current)
{
	current->outfile[index[0]] = NULL;
	current->infile[index[1]] = NULL;
	current->here_doc[index[2]] = NULL;
	return (index);
}

int	*handle_redirections(t_token **tmp, t_cmd *current, int *index)
{
	if ((*tmp)->type == GREAT || (*tmp)->type == GREAT_GREAT)
	{
		if ((*tmp)->next && (*tmp)->next->type == ARG)
		{
			check_direction(current, (*tmp)->type);
			*tmp = (*tmp)->next;
			current->outfile[index[0]] = strdup((*tmp)->value);
			index[0]++;
		}
	}
	else if ((*tmp)->type == LESS)
	{
		if ((*tmp)->next && (*tmp)->next->type == ARG)
		{
			*tmp = (*tmp)->next;
			current->infile[index[1]] = strdup((*tmp)->value);
			index[1]++;
		}
	}
	else if ((*tmp)->type == LESS_LESS)
	{
		aux_handle_redirections(tmp, current, index);
		index[2]++;
	}
	return (null_index(index, current));
}
