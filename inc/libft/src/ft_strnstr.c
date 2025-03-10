/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:13:52 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/10 09:16:06 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

#include <stddef.h>

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t  i;
    size_t  j;

    i = 0;
    if (!*needle)
        return ((char *)haystack);

    while (haystack[i] && i < len)
    {
        j = 0;
        while (haystack[i + j] == needle[j] && i + j < len)
        {
            j++;
            if (!needle[j])
                return ((char *)(haystack + i));
        }
        i++;
    }
    return (NULL);
}

