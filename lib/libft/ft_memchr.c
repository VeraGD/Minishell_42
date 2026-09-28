/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:36:52 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/12 10:57:17 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*found_str;
	unsigned char		ch;

	ch = (unsigned char) c;
	found_str = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (found_str[i] == ch)
			return ((void *) &found_str[i]);
		i++;
	}
	return (NULL);
}
