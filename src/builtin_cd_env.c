/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:02:04 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/16 15:02:06 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Updates the env variables with the new path

   Updates the OLDPWD and PWD env variables with the new path.
   If the argument is a path, I put the whole path in these variables, 
   if it is a folder name I add the folder to the path with a / in between.

   · t_shell *shelly -> principal structure
   · char **argv -> arguments of the comand line
*/
static void	aux_builting_cd(t_shell *shelly, char **argv)
{
	int		i;
	char	**env_split;
	char	*new_line;

	i = 0;
	while (shelly->env[i] != 0)
	{
		new_line = join_env(argv, shelly->env[i], shelly);
		env_split = ft_split(shelly->env[i], '=');
		if (ft_strcmp("OLDPWD", env_split[0]) == 0)
			update_env(shelly, new_line, i, 0);
		if (ft_strcmp("PWD", env_split[0]) == 0)
			update_env(shelly, new_line, i, 0);
		free(new_line);
		new_line = NULL;
		free_split(env_split);
		i++;
	}
	shelly->last_exit = 0;
}

/* Cd builtin

   First check the number of arguments (if there is only one, 
   change path to home, if there are more than two, send an error).
   Then the env is updated in the two valid cases according to arguments,
   and checked if the new path is reachable.

   · t_shell *s -> principal structure
   · char **argv -> arguments of the comand line
*/
void	builtin_cd(t_shell *s, char **arg)
{
	int		flag;

	flag = 0;
	if (arg[1] == NULL)
		flag = 1;
	else if (arg[2] != NULL)
		ft_error(s, "minishelly: cd: too many arguments", 1, 0);
	if (flag == 1)
		aux_builting_cd(s, arg);
	else if (chdir(arg[1]) == 0 || flag == 1)
		aux_builting_cd(s, arg);
	else
		ft_error(s, "minishelly: cd: +: No such file or directory", 1, arg[1]);
}

/* Env builtin

   Print environment variables if there is only one argument (env),
   if there are more arguments print an error.

   · t_shell *s -> principal structure
   · char **argv -> arguments of the comand line
*/
void	builtin_env(t_shell *shelly, char **argv)
{
	int	i;

	i = 0;
	if (argv[1] == NULL)
	{
		while (shelly->env[i] != NULL)
		{
			printf("%s\n", shelly->env[i]);
			i++;
		}
	}
	else
		ft_error(shelly, "env: ‘+’: No such file or directory", 1, argv[1]);
	shelly->last_exit = 0;
}

/* Auxiliary function of the export builtin

   Print environment variables with the string ‘declare -x’ in front
   (used if export is run without further arguments)

   · t_shell *s -> principal structure
*/
void	print_env(t_shell *shelly)
{
	int	i;

	i = 0;
	while (shelly->env[i] != NULL)
	{
		printf("declare -x %s\n", shelly->env[i]);
		i++;
	}
}
