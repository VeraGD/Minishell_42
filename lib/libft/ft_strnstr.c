/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:28:45 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/12 13:16:30 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t slen)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (find[0] == 0)
		return ((char *)str);
	while (str[i] != '\0' && i < slen)
	{
		j = 0;
		while (str[i + j] == find[j] && find[j] != '\0'
			&& (i + j) < slen)
		{
			j++;
			if (find[j] == '\0')
				return ((char *) str + i);
		}
		i++;
	}
	return (NULL);
}
