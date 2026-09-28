/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:15:11 by narrospi          #+#    #+#             */
/*   Updated: 2024/09/17 11:43:19 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(long num)
{
	int	count;

	count = 0;
	if (num < 0)
	{
		count++;
		num *= -1;
	}
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static char	*book_memory(int len)
{
	char	*temp;

	temp = malloc((len +1) * sizeof(char));
	if (!temp)
		return (NULL);
	temp[0] = '0';
	return (temp);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		i;
	long	number;

	number = n;
	len = count_digits(n);
	result = book_memory(len);
	if (number == 0)
		result[0] = '0';
	if (number < 0)
	{
		result[0] = '-';
		number *= -1;
	}
	i = len - 1;
	while (number != 0)
	{
		result[i] = (number % 10) + '0';
		number = number / 10;
		i--;
	}
	result[len] = '\0';
	return (result);
}
