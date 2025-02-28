/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:58:53 by mkling            #+#    #+#             */
/*   Updated: 2025/02/28 11:01:40 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1025
#endif

char	*ft_strjoinfree(char *s1, char const *s2)
{
	char	*result;
	size_t	len;
	size_t	index_s1;
	size_t	index_s2;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = ft_calloc(len, sizeof(char));
	if (!result || !s1 || !s2)
		return (NULL);
	index_s1 = 0;
	index_s2 = 0;
	while (s1[index_s1] != '\0')
	{
		result[index_s1] = s1[index_s1];
		index_s1++;
	}
	while (s2[index_s2] != '\0')
	{
		result[index_s1 + index_s2] = s2[index_s2];
		index_s2++;
	}
	result[index_s1 + index_s2] = '\0';
	free(s1);
	return (result);
}

char	*read_till_newline(int fd, char *static_buffer)
{
	char	*current_buffer;
	int		read_status;
	char	*tmp;

	if (!static_buffer)
		static_buffer = ft_calloc(1, sizeof(char));
	if (!static_buffer)
		return (NULL);
	current_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!current_buffer)
		return (NULL);
	read_status = 1;
	while (read_status > 0)
	{
		read_status = read(fd, current_buffer, BUFFER_SIZE);
		if (read_status == -1)
			return (free(current_buffer), NULL);
		current_buffer[read_status] = '\0';
		tmp = ft_strjoinfree(static_buffer, current_buffer);
		static_buffer = tmp;
		if (ft_strchr(current_buffer, '\n'))
			break ;
	}
	free(current_buffer);
	return (static_buffer);
}

char	*cut_out_line(char *buffer)
{
	size_t	index;
	char	*cut_line;

	index = 0;
	if (!buffer[index])
		return (NULL);
	while (buffer[index] && buffer[index] != '\n')
		index++;
	cut_line = ft_calloc(index + 2, sizeof(char));
	index = 0;
	while (buffer[ft_strlen(buffer)] && buffer[index] != '\n')
	{
		cut_line[index] = buffer[index];
		index++;
	}
	cut_line[index] = buffer[index];
	index++;
	cut_line[index] = '\0';
	return (cut_line);
}

char	*keep_leftover(char *buffer)
{
	size_t	newline_index;
	size_t	buffer_index;
	char	*leftover;

	newline_index = 0;
	if (!buffer)
		return (NULL);
	while (buffer[newline_index] && buffer[newline_index] != '\n')
		newline_index++;
	newline_index++;
	leftover = ft_calloc(ft_strlen(buffer) - newline_index + 2, sizeof(char));
	if (!leftover)
		return (NULL);
	buffer_index = -1;
	while (buffer[newline_index + ++buffer_index - 1])
		leftover[buffer_index] = buffer[newline_index + buffer_index];
	free(buffer);
	if (!*leftover)
	{
		free(leftover);
		leftover = NULL;
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_till_newline(fd, buffer);
	if (!buffer)
		return (free(buffer), NULL);
	line = cut_out_line(buffer);
	buffer = keep_leftover(buffer);
	return (line);
}
