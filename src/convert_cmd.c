/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:19:33 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 11:19:36 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_arguments(t_token *tmp, t_cmd *current, int i, t_shell *s)
{
	if (!current->argv)
	{
		current->argv = malloc(MAX_ARGS * sizeof(char *));
		if (!current->argv)
		{
			ft_error(s, "malloc error", 1, 0);
			return (0);
		}
		ft_memset(current->argv, 0, MAX_ARGS * sizeof(char *));
	}
	if (i < MAX_ARGS - 1)
	{
		current->argv[i] = parse_expansion(tmp->value, s);
		current->argv[++(i)] = NULL;
	}
	return (i);
}

static t_cmd	*aux_aux_c_tokens(t_cmd *current, t_shell *s, int *arg_index)
{
	current = handle_pipe(s, current);
	*arg_index = 0;
	return (current);
}

static t_cmd	*aux_convert_tokens(int *index, t_cmd *current,
	t_cmd *cmd_list, t_shell *shelly)
{
	t_token	*tmp;
	int		arg_index;

	tmp = shelly->tokens;
	arg_index = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			current = aux_aux_c_tokens(current, shelly, &arg_index);
		else if (tmp->type == GREAT || tmp->type == GREAT_GREAT
			|| tmp->type == LESS || tmp->type == LESS_LESS)
			index = handle_redirections(&tmp, current, index);
		else
		{
			if (!current)
			{
				current = create_new_cmd(shelly);
				cmd_list = current;
			}
			arg_index = handle_arguments(tmp, current, arg_index, shelly);
		}
		tmp = tmp->next;
	}
	free(index);
	return (cmd_list);
}

t_cmd	*convert_tokens_to_cmd(t_shell *shelly)
{
	int		*index;

	index = (int *)malloc(3 * sizeof(int));
	if (!index)
	{
		ft_error(shelly, "malloc error", 1, 0);
		return (NULL);
	}
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	return (aux_convert_tokens(index, NULL, NULL, shelly));
}
