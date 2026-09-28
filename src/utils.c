/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:30:49 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:30:52 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_quotation(char *str, t_shell *shelly)
{
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	in_single = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	shelly->double_q = in_double;
	shelly->single_q = in_single;
	return (!in_double && !in_single);
}

t_token	*find_last_node(t_token	*list)
{
	if (list == NULL)
		return (NULL);
	while (list && list->next)
		list = list->next;
	return (list);
}

/* void	print_tokens(t_token *tokens)
{
	t_token	*current;

	printf("print_tokens\n");
	current = tokens;
	while (current)
	{
		printf("value: %s  -  type: %d  - position: %d \n",
			ft_strtrim(current->value, " \" "),
		current->type, current->position);
		current = current->next;
	}
} */

// void	print_cmd(t_cmd *cmds)
// {
// 	t_cmd	*current = cmds;
// 	int		i;

// 	while (current)
// 	{
// 		i = 0;
// 		printf("\nNuevo comando:\n");
// 		while (current->argv[i])
// 		{
// 			printf("  Arg[%d]: %s\n", i, current->argv[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (current->infile[i])
// 		{
// 			printf("  Infile[%d]: %s\n", i, current->infile[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (current->outfile[i])
// 		{
// 			printf("  Outfile[%d]: %s\n", i, current->outfile[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (current->here_doc[i])
// 		{
// 			printf("  here_doc[%d]: %s\n", i, current->here_doc[i]);
// 			i++;
// 		}
// 		printf("  Append: %d\n", current->append);
// 		printf("  fd inf: %d\n", current->fd_inf);
// 		printf("  fd out: %d\n", current->fd_out);
// 		/* printf("  Infile: %s\n", current->infile ? current->infile : 
// "(null)");
// 		printf("  Outfile: %s\n", current->outfile ? current->outfile : 
// 		"(null)");
// 		printf("  Append: %d\n", current->append);
// 		printf("  here_doc: %s\n", current->here_doc); */
// 		current = current->next;
// 	}
// }

/* void	print_split(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		printf("input[%d]: %s\n", i, args[i]);
		i++;
	}
} */

/*
This function is an excerpt from the handle_directions
function to comply with the norminette
*/
void	check_direction(t_cmd *current, int type)
{
	if (type == GREAT_GREAT)
		current->append = 1;
	else
		current->append = 0;
}

int	num_pipex(t_shell *shelly)
{
	t_cmd	*current;
	int		i;

	current = shelly->cmd_tree;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	*aux_path(char **split1, char **split2, char *join, char *join_cmd)
{
	free_split(split1);
	free_split(split2);
	free(join);
	return (join_cmd);
}
