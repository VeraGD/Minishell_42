/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_cd_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:33:45 by veragarc          #+#    #+#             */
/*   Updated: 2025/03/25 14:33:47 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Auxiliary function of the echo builtin

   Checks if echo is to be executed with the -n argument.
   To do this, it returns a flag to see if an argument is skipped (-n) or
   prints all arguments after echo.

   · char *str -> second argument in the line comand
*/
static int	check_echo_option(char *str)
{
	if (ft_strcmp(str, "-n") == 0)
		return (1);
	else
		return (0);
}

/* Auxiliary function of the echo builtin

   Pass the -n argumnts just after echo.

   · char **str -> arguments of the propmt
   · int i -> index to print the arguments
*/
static int	pass_echo_option(char **str, int i)
{
	while (str[i])
	{
		if (ft_strcmp(str[i], "-n") != 0)
			break ;
		i++;
	}
	return (i);
}

/* Echo builtin

   Print all arguments after the echo word (except flag -n),
   check whether to print $?.

   · t_cmd *current -> current argument tree
   · t_shell *s -> principal structure
*/
void	builtin_echo(t_cmd *current, t_shell *shelly)
{
	size_t	i;
	int		flag;
	size_t	space;

	space = ft_strlen_double(current->argv);
	i = 1;
	flag = 0 + check_echo_option(current->argv[i]);
	i = pass_echo_option(current->argv, i);
	while (current->argv[i])
	{
		if (ft_strcmp(current->argv[i], "$?") != 0)
		{
			printf("%s", current->argv[i]);
			if (space != i + 1)
				printf(" ");
		}
		else
			printf("%d", shelly->last_exit);
		i++;
	}
	if (flag == 0)
		printf("\n");
	shelly->last_exit = 0;
}

/* Auxiliary function of the cd builtin

   Finds the path to Home in the environment variables,
   returns the new line to put in the received environment variable.

   · char *path -> env line to be changed (PWD or OLDPWD)
   · t_shell *shelly -> principal structure
*/
static char	*aux_join_env(char *path, t_shell *shelly)
{
	char	**split_env;
	char	*temp;
	char	*new_put;

	split_env = ft_split(path, '=');
	temp = ft_strjoin(split_env[0], "=");
	search_env_var(shelly, "HOME", NULL, 0);
	new_put = ft_strjoin(temp, shelly->env_var);
	if (chdir(shelly->env_var) != 0 && path[0] == 'O')
		ft_error(shelly, "home chdir error", 1, 0);
	free_split(split_env);
	free(temp);
	return (new_put);
}

/* Auxiliary function of the cd builtin

   Checks all cases of cd and returns the complete new line
   (ex: PWD=....) of the env to be placed.

   · char **argv -> arguments of the comand line
   · char *path -> env line to be changed (PWD or OLDPWD)
   · t_shell *shelly -> principal structure
*/
char	*join_env(char **argv, char *path, t_shell *shelly)
{
	char	*new_put;
	char	*temp;
	char	**split_env;

	if (argv[1] == NULL)
		new_put = aux_join_env(path, shelly);
	else if (argv[1][0] != '/')
	{
		temp = ft_strjoin(path, "/");
		new_put = ft_strjoin(temp, argv[1]);
		free(temp);
	}
	else
	{
		split_env = ft_split(path, '=');
		temp = ft_strjoin(split_env[0], "=");
		new_put = ft_strjoin(temp, argv[1]);
		free(temp);
		free_split(split_env);
	}
	return (new_put);
}
