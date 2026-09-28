/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:37:50 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/13 13:04:50 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen (s1);
	j = len - 1;
	while (s1[i] && check_trim(set, s1[i]))
		i++;
	while (j >= i && check_trim(set, s1[j]))
		j--;
	str = (char *)malloc((j - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy (str, &s1[i], j - i + 2);
	return (str);
}
