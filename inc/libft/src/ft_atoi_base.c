/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:58:43 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/28 10:58:45 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <unistd.h>

int	clean_base(char *base)
{
	int	i;
	int	j;

	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if ((base[i] >= 9 && base[i] <= 13) || base[i] == ' ' )
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_empty_sign(char *str, int i, int *minus)
{
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*minus = *minus * -1;
		i++;
	}
	return (i);
}

int	ft_atoi_anybase(char *str, char *base, int i)
{
	int		j;
	int		size;
	long	number;

	number = 0;
	size = ft_strlen(base);
	while (str[i])
	{
		j = 0;
		while (base[j])
		{
			if (str[i] == base[j])
				number = number * size + j;
			j++;
		}
		i++;
	}
	return ((int)number);
}

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		minus[1];

	if (!clean_base(base))
		return (0);
	i = 0;
	*minus = 1;
	i = ft_empty_sign(str, i, minus);
	return (ft_atoi_anybase(str, base, i) * *minus);
}
