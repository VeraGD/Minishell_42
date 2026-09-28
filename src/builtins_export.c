/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:34:33 by veragarc          #+#    #+#             */
/*   Updated: 2025/03/25 14:34:35 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Auxiliary function of the function aux_export_up

	Gets the variable to be entered in the env, only the variable name,
	not variable and field.

	· char **str -> arguments of the comand line
	. int *flag -> memory address of the flag used
	· t_shell *s -> principal structure
*/
static char	*export_up_search(char *str, int *flag, t_shell *shelly)
{
	char	**search_all;
	char	*to_search;

	search_all = ft_split(str, '=');
	to_search = malloc(ft_strlen(search_all[0]) * sizeof(char *));
	if (!to_search)
	{
		ft_error(shelly, "malloc error", 1, 0);
		return (NULL);
	}
	ft_strlcpy(to_search, search_all[0], ft_strlen(search_all[0]) + 1);
	if (search_all[1] != NULL)
		*flag = 0;
	else
	{
		free(to_search);
		to_search = NULL;
		*flag = 1;
	}
	free_split(search_all);
	return (to_search);
}

/* Auxiliary function of the export builtin

	Gets the variable to be entered in the env, only the variable name,
	not variable and field.
	Returns an error if the variable to be entered in the env does not
	start with a letter or a _.

	· char **a -> arguments of the comand line
	. int *flag -> memory address of the flag used
	· t_shell *s -> principal structure
*/
static char	*aux_export_up(char *a, int *flag, t_shell *s)
{
	char	*to_search;

	if (!(ft_isalpha(a[0]) || a[0] == '_'))
	{
		*flag = 1;
		ft_error(s, "minishelly: export: '+': not valid identifier", 1, a);
		return (NULL);
	}
	s->last_exit = 0;
	if (a[ft_strlen(a) - 1] != '=')
		to_search = export_up_search(a, flag, s);
	else
	{
		to_search = (char *)malloc(ft_strlen(a));
		if (!to_search)
		{
			ft_error(s, "malloc error", 1, 0);
			return (NULL);
		}
		ft_strlcpy(to_search, a, ft_strlen(a));
	}
	return (to_search);
}

/* Auxiliary function of the export builtin

   Update the env with the new variable if necessary.

   · char **argv -> arguments of the comand line
   . int *flag -> memory address of the flag used
   · t_shell *shelly -> principal structure
   . int i -> index used to update the env
   
*/
static void	aux_export_down(char *argv, int *flag, t_shell *shelly, int i)
{
	if (*flag == 0 && argv[ft_strlen(argv) - 1] == '=')
	{
		*flag = 2;
		update_env(shelly, argv, i, 0);
	}
	if (*flag == 0)
		update_env(shelly, argv, i, 0);
}

void	heart_export(char *argv, t_shell *shelly, int i, int flag)
{
	char	**env_split;
	char	*to_search;

	to_search = aux_export_up(argv, &flag, shelly);
	if (to_search != NULL)
	{
		while (shelly->env[i] != 0 && flag == 0)
		{
			env_split = ft_split(shelly->env[i], '=');
			if (ft_strcmp(to_search, env_split[0]) == 0)
			{
				update_env(shelly, argv, i, 0);
				free_split(env_split);
				flag = 2;
				break ;
			}
			free_split(env_split);
			i++;
		}
		aux_export_down(argv, &flag, shelly, i);
		if (flag == 0 || flag == 2)
			check_if_free(to_search);
	}
}

/* Export builtin

   Introduces a new environment variable as the last variable.
   If you want to enter a variable that does not start with a letter or a _,
   an error is printed.
	If you want to enter a variable without =, nothing is done.
	If you want to enter a variable that ends in equal, without a field,
	you enter it as it is (ex: hello=), and if this variable has a field,
	equal in the middle, you enter it as it is (ex: hello=aa).Nothing is
	printed, just added.
	If there is more than one argument, but the first one, the variable,
	is entered correctly, the variable is added.
	If only export is entered without arguments, all environment variables
	are printed.

   · char **argv -> arguments of the comand line
   · t_shell *shelly -> principal structure
   · int i -> counter used in the function
   · int flag -> flag used in the function
*/
void	builtin_export(char **argv, t_shell *shelly, int i, int flag)
{
	int	j;

	j = 1;
	while (argv[j])
	{
		heart_export(argv[j], shelly, i, flag);
		j++;
	}
	if (argv[1] == NULL)
		print_env(shelly);
}
