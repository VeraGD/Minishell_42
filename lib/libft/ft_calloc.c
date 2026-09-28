/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:19:36 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/12 14:57:44 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_items, size_t size)
{
	unsigned char	*str;

	str = malloc(num_items * size);
	if (!str)
		return (NULL);
	ft_bzero(str, num_items * size);
	return (str);
}
