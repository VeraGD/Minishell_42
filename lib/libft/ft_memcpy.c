/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:45:56 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/10 12:49:28 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	size_t			i;
	unsigned char	*dest_str_cp;
	unsigned char	*src_str_cp;

	i = 0;
	dest_str_cp = (unsigned char *) dest_str;
	src_str_cp = (unsigned char *) src_str;
	while (i < n)
	{
		dest_str_cp[i] = src_str_cp[i];
		i++;
	}
	return (dest_str);
}
