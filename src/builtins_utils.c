/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:36:50 by veragarc          #+#    #+#             */
/*   Updated: 2025/03/25 14:36:53 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function to compare two strings

   Compares two strings, if they are the same it returns 0,
   otherwise the difference between their first different
   ascii character.

   · char *s1 -> first string to compare
   · char *s2 -> second string to compare
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/* Function to calculate the size of a char **

   Calculate how many char * there are inside a char **.

   · char **argv -> double pointer from which the len calculated
*/
size_t	ft_strlen_double(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

/* Function that updates a line of the env

   Function that places the new line provided in the env in the indicated
   index. A new env is created with this line, deleting the existing one,
   to facilitate memory management.

   · t_shell *shelly -> principal structure
   · char *new_line -> new env line
   · size_t index -> index of this new line
   · size_t i -> counter used in the function
*/
void	update_env(t_shell *shelly, char *new_line, size_t index, size_t i)
{
	size_t	len;
	char	**new_env;

	len = ft_strlen_double(shelly->env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (ft_error(shelly, "malloc error", 1, 0));
	while (i < len)
	{
		new_env[i] = shelly->env[i];
		i++;
	}
	if (index == len)
	{
		new_env[len] = ft_strdup(new_line);
		new_env[len + 1] = NULL;
	}
	else if (index < len)
	{
		free(new_env[index]);
		new_env[index] = ft_strdup(new_line);
		new_env[len] = NULL;
	}
	free(shelly->env);
	shelly->env = new_env;
}

/* Auxiliary function of the search_env_var function

   Returns the field of the variable searched for, to be used in the
   search_env_var function.

   · t_shell *shelly -> principal structure
   · char *home -> string used in the function
*/
static void	search_env_var_aux(t_shell *shelly, char *home)
{
	char	**home_split;

	home_split = ft_split(home, '=');
	shelly->env_var = (char *)malloc(ft_strlen(home_split[1]) + 1);
	if (!shelly->env_var)
		return (ft_error(shelly, "malloc error", 1, 0));
	ft_strlcpy(shelly->env_var, home_split[1], ft_strlen(home_split[1]) + 1);
	free_split(home_split);
}

/* Function that stores the field of an env variable in the principal structure

   Function that searches for the variable provided in the env, and stores
   this result in the main structure, in env_var.
   It only saves the field of the variable, if the variable does not exists,
   it saves an empty string.

   · t_shell *shelly -> principal structure
   · char *to_serch -> variable to search
   · char *home -> string used in the function
   · int i -> counter used in the function
*/
void	search_env_var(t_shell *shelly, char *to_search, char *home, int i)
{
	char	**env_split;

	free_env_var(shelly);
	while (shelly->env[i] != 0)
	{
		env_split = ft_split(shelly->env[i], '=');
		if (ft_strcmp(to_search, env_split[0]) == 0)
		{
			home = shelly->env[i];
			free_split(env_split);
			break ;
		}
		free_split(env_split);
		i++;
	}
	if (home == NULL)
		shelly->env_var = ft_strdup(" ");
	else
		search_env_var_aux(shelly, home);
}
