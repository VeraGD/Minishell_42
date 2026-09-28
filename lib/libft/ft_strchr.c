/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:40 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/10 15:16:02 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int search_str)
{
	int		i;
	char	character;

	character = (char)search_str;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == character)
			return ((char *) &str[i]);
		i++;
	}
	if (character == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
