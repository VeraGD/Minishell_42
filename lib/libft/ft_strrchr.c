/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:47:47 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/11 16:04:59 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	character;
	char	*found_str;

	character = (char)c;
	i = 0;
	found_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == character)
		{
			found_str = (char *) &str[i];
		}
		i++;
	}
	if (character == '\0')
		return ((char *)&str[i]);
	return (found_str);
}
