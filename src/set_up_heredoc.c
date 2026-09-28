/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:06:47 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/05 16:06:50 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	aux_file_up(t_cmd *cmd, int i, char *line)
{
	while (1)
	{
		if (ft_strcmp("1679", cmd->here_doc[i]) == 0)
			break ;
		line = readline(PURPLE"> "RESET);
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->here_doc[i]) == 0)
		{
			free(line);
			break ;
		}
	}
	i++;
	return (i);
}

static void	aux_file_down(t_cmd *cmd, int i, char *line, int fd_tmp)
{
	while (1)
	{
		if (ft_strcmp("1679", cmd->here_doc[i]) == 0)
			break ;
		line = readline(PURPLE"> "RESET);
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->here_doc[i]) == 0)
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		write(fd_tmp, "\n", 1);
		free(line);
	}
}

static void	aux_create_file(t_shell *s, t_cmd *cmd, char *line, int fd_tmp)
{
	int	i;

	i = 0;
	while (cmd->here_doc[i])
	{
		if (ft_strcmp("1679", cmd->here_doc[i]) == 0)
		{
			ft_error(s, "minishelly: syntax error near token `<<'", 2, 0);
			unlink("tmp.txt");
			break ;
		}
		if (cmd->here_doc[i + 1] != NULL)
			i = aux_file_up(cmd, i, line);
		aux_file_down(cmd, i, line, fd_tmp);
		if (ft_strcmp("1679", cmd->here_doc[i]) == 0)
		{
			ft_error(s, "minishelly: syntax error near token `<<'", 2, 0);
			unlink("tmp.txt");
			break ;
		}
		close(fd_tmp);
		i++;
	}
}

void	create_file(t_cmd *cmd, t_shell *s)
{
	int		fd_tmp;
	char	*line;

	fd_tmp = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		return (ft_error(s, "error fd here doc", 2, 0));
	line = 0;
	aux_create_file(s, cmd, line, fd_tmp);
}
