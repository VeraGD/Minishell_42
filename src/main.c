/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:46 by veragarc          #+#    #+#             */
/*   Updated: 2025/04/24 14:00:49 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// http://patorjk.com/software/taag/#p=testall&f=Ogre&t=Minishelly
static void	print_big_minishelly(void)
{
	printf(
		YELLOW"        _       _     _          _ _       \n"
		"  /\\/\\ (_)_ __ (_)___| |__   ___| | |_   _ \n"
		" /    \\| | '_ \\| / __| '_ \\ / _ \\ | | | | |\n"
		"/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | | |_| |\n"
		"\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|\\__, |\n"
		"                                     |___/ \n");
}

static void	print_welcome_mesagge(void)
{
	printf(YELLOW"\n*******************************************\n");
	printf(CYAN"        welcome to shelly %s\n", getenv("USER"));
	printf(YELLOW"*******************************************\n\n");
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shelly;

	(void)argv;
	rl_catch_signals = 0;
	if (argc != 1)
	{
		printf("Error. Number of arguments incorrect.\n");
		exit (1);
	}
	init_shell(&shelly, env);
	print_big_minishelly();
	print_welcome_mesagge();
	prompt_loop(&shelly);
	free_shell(&shelly);
	rl_clear_history();
	return (0);
}
