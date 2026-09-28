/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:35:19 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/11 12:01:07 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_copy;
	char	*src_copy;
	size_t	i;

	dest_copy = (char *) dest;
	src_copy = (char *) src;
	i = 0;
	if (dest_copy > src_copy)
		while (n-- > 0)
			dest_copy[n] = src_copy[n];
	else
	{
		while (i < n)
		{
			dest_copy[i] = src_copy[i];
			i++;
		}
	}
	return (dest);
}
