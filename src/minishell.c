/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:29:37 by narrospi          #+#    #+#             */
/*   Updated: 2025/04/11 12:29:40 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_flag_signal = 0;

void	init_shell(t_shell *shelly, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return (ft_error(shelly, "malloc error", 1, 0));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	shelly->env = new_env;
	shelly->last_exit = 0;
	shelly->exit = 0;
	shelly->tokens = NULL;
	shelly->cmd_tree = NULL;
	shelly->env_var = NULL;
	shelly->pids = NULL;
}

void	execute_builtin(t_cmd *cmd, t_shell *shelly, char *cc)
{
	if (!ft_strcmp(cc, "echo"))
		builtin_echo(cmd, shelly);
	else if (!ft_strcmp(cc, "pwd"))
		builtin_pwd(shelly);
	else if (!ft_strcmp(cc, "env"))
		builtin_env(shelly, cmd->argv);
	else if (!ft_strcmp(cc, "export"))
		builtin_export(cmd->argv, shelly, 0, 0);
	else if (!ft_strcmp(cc, "cd"))
		builtin_cd(shelly, cmd->argv);
	else if (!ft_strcmp(cc, "unset"))
		builtin_unset(shelly, cmd->argv, 0);
	else if (!ft_strcmp(cc, "exit"))
		builtin_exit(shelly, cmd->argv);
}

static void	execute_command(char *input, t_shell *shelly)
{
	char	**tokens;

	if (check_quotation(input, shelly))
	{
		tokens = ft_split_up(shelly, input);
		init_token(tokens, shelly);
		check_built_comand(shelly);
		setup_pipe(shelly);
		free_split(tokens);
		if (shelly->exit == 1)
		{
			reset_up(shelly);
			free_shell(shelly);
			rl_clear_history();
			free(input);
			exit(shelly->last_exit);
		}
	}
	else
		ft_error(shelly, "Syntax error, quotes", 1, 0);
}

static void	prompt_loop_exit(t_shell *shelly)
{
	printf("exit\n");
	free_shell(shelly);
	rl_clear_history();
	exit(0);
}

void	prompt_loop(t_shell *shelly)
{
	char	*input;
	char	*tmp;

	handle_signals();
	while (42)
	{
		g_flag_signal = 0;
		tmp = readline(CYAN"minishelly$ "RESET);
		if (!tmp)
			prompt_loop_exit(shelly);
		input = ft_strtrim(tmp, " \t");
		free(tmp);
		g_flag_signal = 1;
		if (input[0] != '\0')
		{
			if (!wrong_pipe(shelly, input))
			{
				add_history(input);
				execute_command(input, shelly);
			}
		}
		if (input[0] != '\0')
			reset_up(shelly);
		free(input);
	}
}
