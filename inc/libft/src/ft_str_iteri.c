/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_iteri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:33:57 by mkling            #+#    #+#             */
/*   Updated: 2025/02/26 14:14:17 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t			len;
	unsigned int	i;

	len = ft_strlen(s);
	i = 0;
	while (len > i)
	{
		(*f)(i, &s[i]);
		i++;
	}
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			len;
	unsigned int	i;

	len = ft_strlen(s);
	result = malloc((len + 1) * sizeof(char));
	if (!result || !f || !s)
		return (NULL);
	ft_memcpy(result, s, len);
	i = 0;
	while (i < len)
	{
		result[i] = (*f)(i, result[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
