/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:29:19 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:29:21 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return (ft_error(s, "malloc error", 1, 0));
static void	add_token(char *str, int type, t_token **tokens, int position)
{
	t_token	*new_node;
	t_token	*last;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->value = ft_strdup(str);
	new_node->type = type;
	new_node->position = position;
	new_node->next = NULL;
	if (!(*tokens))
	{
		*tokens = new_node;
		return ;
	}
	last = find_last_node(*tokens);
	last->next = new_node;
}

void	init_token(char **tokens, t_shell *shelly)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], IS_PIPE))
			add_token(tokens[i], PIPE, &(shelly->tokens), i);
		else if (!ft_strcmp(tokens[i], IS_D_GREAT))
			add_token(tokens[i], GREAT_GREAT, &(shelly->tokens), i);
		else if (!ft_strcmp(tokens[i], IS_GREAT))
			add_token(tokens[i], GREAT, &(shelly->tokens), i);
		else if (!ft_strcmp(tokens[i], IS_D_LESS))
			add_token(tokens[i], LESS_LESS, &(shelly->tokens), i);
		else if (!ft_strcmp(tokens[i], IS_LESS))
			add_token(tokens[i], LESS, &(shelly->tokens), i);
		else
			add_token(tokens[i], ARG, &(shelly->tokens), i);
		i++;
	}
	shelly->cmd_tree = convert_tokens_to_cmd(shelly);
}

bool	wrong_pipe(t_shell *s, char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	if (input[0] == '|')
	{
		ft_error(s, "minishelly: syntax error near token `|'", 2, 0);
		return (true);
	}
	else if (input[len] == '|' || (input[len] == '>' || input[len] == '<'))
	{
		ft_error(s, "minishelly: syntax error near token `newline'", 2, 0);
		return (true);
	}
	else if (input[0] == '>' || input[0] == '<')
	{
		return (true);
	}
	return (false);
}

int	is_not_empty_or_spaces(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
