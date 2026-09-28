/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset_exit_pwd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:36:02 by veragarc          #+#    #+#             */
/*   Updated: 2025/03/25 14:36:04 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Auxiliary function of the unset builtin

   Check that the variable passed as an argument is correct. That is,
   if it starts with letters or _, and if it has no equals, it does not
   contain the variable field.

   · t_shell *shelly -> principal structure
   · char **argv -> arguments of the comand line
*/
static int	search_equal(t_shell *shelly, char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' && (arg[1] == 's' || arg[1] == 'z') && arg[2] == '\0')
	{
		ft_error(shelly, "minishelly: unset: +: invalid option", 1, arg);
		printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
	}
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		shelly->last_exit = 1;
		return (1);
	}
	shelly->last_exit = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	heart_unset(t_shell *shelly, char *argv, int i)
{
	char	**env_split;
	int		j;

	while (shelly->env[i])
	{
		env_split = ft_split(shelly->env[i], '=');
		if (ft_strcmp(argv, env_split[0]) == 0)
		{
			free(shelly->env[i]);
			j = i;
			while (shelly->env[j])
			{
				shelly->env[j] = shelly->env[j + 1];
				j++;
			}
			free_split(env_split);
			break ;
		}
		free_split(env_split);
		i++;
	}
}

/* Unset builtin

   Removes an en variable if the variable name is passedas an
   argument, without =.
   If more arguments are passed, but the first one is an env variable,
   the variable is deleted.

   · t_shell *shelly -> principal structure
   · char **argv -> arguments of the comand line
   · int i -> counter used in the builtin
*/
void	builtin_unset(t_shell *shelly, char **argv, int i)
{
	int		k;

	k = 1;
	while (argv[k])
	{
		i = 0;
		if (search_equal(shelly, argv[k]) == 0)
			heart_unset(shelly, argv[k], i);
		k++;
	}
}

/* Auxiliary function of the export builtin

   Frees the string if it is not null.

   · char *to_search -> string to free
*/
void	check_if_free(char *to_search)
{
	if (to_search != NULL)
		free(to_search);
}
