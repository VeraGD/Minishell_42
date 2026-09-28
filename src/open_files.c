/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:10:46 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/05 16:10:48 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	aux_create_f(t_shell *s, t_cmd *c, size_t i, int fd)
{
	char	*f;
	size_t	in_len;

	in_len = ft_strlen_double(c->infile);
	while (c->infile[i])
	{
		if (i == in_len - 1 || (int)in_len - 1 == -1)
			break ;
		else
		{
			fd = open(c->infile[i], O_RDONLY);
			if (fd < 0)
			{
				f = c->infile[i];
				c->fd_inf = -2;
				ft_error(s, "minishelly: +: No such file or directory", 1, f);
				return ;
			}
			close(fd);
		}
		i++;
	}
}

void	create_all_files(t_shell *s, t_cmd *c)
{
	size_t	i;
	int		fd;
	size_t	out_len;

	out_len = ft_strlen_double(c->outfile);
	i = 0;
	while (c->outfile[i])
	{
		if (i == out_len - 1 || (int)out_len - 1 == -1)
			break ;
		else
		{
			fd = open(c->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		i++;
	}
	i = 0;
	aux_create_f(s, c, i, fd);
}

static void	aux_open_f(t_shell *shelly, t_cmd *c)
{
	size_t	out_len;
	size_t	o;

	out_len = ft_strlen_double(c->outfile);
	o = out_len -1;
	if ((int)ft_strlen_double(c->outfile) == 0)
		c->fd_out = -1;
	else if (c->outfile[out_len - 1] != NULL && c->append == 0)
	{
		c->fd_out = open(c->outfile[o], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (c->fd_out < 0)
		{
			c->fd_out = -2;
			printf("out %s\n", c->outfile[ft_strlen_double(c->outfile) - 1]);
			return (ft_error(shelly, "Open fd error", 1, 0));
		}
	}
	else if (c->outfile[o] != NULL && c->append == 1 && ((int)o > -1))
		c->fd_out = open(c->outfile[o], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		c->fd_out = -1;
}

void	open_files(t_shell *shelly, t_cmd *c)
{
	size_t	in_len;

	in_len = ft_strlen_double(c->infile);
	if (c->infile[in_len - 1] != NULL && (int)in_len - 1 > -1)
	{
		c->fd_inf = open(c->infile[in_len - 1], O_RDONLY);
		if (c->fd_inf < 0)
		{
			c->fd_inf = -2;
			return (ft_error(shelly, "Open fd error", 1, 0));
		}
	}
	else
		c->fd_inf = -1;
	aux_open_f(shelly, c);
}
