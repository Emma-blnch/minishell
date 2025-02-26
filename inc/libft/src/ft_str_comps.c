/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_comps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:50:50 by mkling            #+#    #+#             */
/*   Updated: 2025/02/26 14:15:00 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = -1;
	while (string[++i])
		if (string[i] == (unsigned char)searchedChar)
			return ((char *)&string[i]);
	if (string[i] == (unsigned char)searchedChar)
		return ((char *)&string[i]);
	return (NULL);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return (-1);
	i = 0;
	while ((s1[i] && s2[i]) && i < n - 1)
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	while (i < len)
	{
		if ((i + needle_len) > len)
			return (NULL);
		if (haystack[i] == needle[0]
			&& (ft_strncmp(needle, &haystack[i], needle_len) == 0))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
