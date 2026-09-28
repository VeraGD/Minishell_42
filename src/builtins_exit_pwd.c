/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:15:19 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/05 16:15:22 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	aux_exit_num(t_shell *shelly, char **argv)
{
	if (ft_atoi(argv[1]) >= 0 && ft_atoi(argv[1]) <= 255)
		shelly->last_exit = ft_atoi(argv[1]);
	else if (ft_atoi(argv[1]) > 255)
		shelly->last_exit = ft_atoi(argv[1]) - 256;
	else
		shelly->last_exit = ft_atoi(argv[1]) + 256;
}

static int	ft_isdigit_double(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/* Exit builtin

   Set the exit variable to 1 in order to be able to exit the
   programme later on.

   · t_shell *shelly -> principal structure
   · char **argv -> arguments of the comand line
*/
void	builtin_exit(t_shell *s, char **argv)
{
	char	*a;

	printf("exit\n");
	if (argv[2] != NULL)
		ft_error(s, "minishelly: exit: too many arguments", 1, 0);
	else if (argv[1] != NULL)
	{
		a = ft_strdup(argv[1]);
		if (ft_isdigit_double(argv[1]) == 1)
			aux_exit_num(s, argv);
		else
		{
			ft_error(s, "minishell: exit: +: numeric argument required", 2, a);
			free(a);
		}
		s->exit = 1;
	}
	else
	{
		s->last_exit = 0;
		s->exit = 1;
	}
}

/* Pwd builtin

   Print the current path of the program, if there is more than
   one argument (pwd) it prints an error.

   · t_shell *shelly -> principal structure
*/
void	builtin_pwd(t_shell *shelly)
{
	char	cwd[1024];

	if (shelly->cmd_tree->argv[1] != NULL)
		ft_error(shelly, "pwd: too many arguments", 1, 0);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			shelly->last_exit = 0;
			printf("%s\n", cwd);
		}
		else
			ft_error(shelly, "pwd getcwd error", 1, 0);
	}
}
