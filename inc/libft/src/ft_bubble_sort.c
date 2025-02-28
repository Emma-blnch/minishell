/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:59:13 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/28 10:59:16 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_bubble_sort(int *num_array, int size_array)
{
	int	index1;
	int	index2;

	index1 = 0;
	while (index1 < size_array)
	{
		index2 = 0;
		while (index2 < size_array - index1 - 1)
		{
			if (num_array[index2] > num_array[index2 + 1])
				ft_swap_int(&num_array[index2], &num_array[index2 + 1]);
			index2++;
		}
		index1++;
	}
}
