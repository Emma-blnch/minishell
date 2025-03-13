/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:16:32 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 10:17:33 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_eof(char *word)
{
	write(2, "warning: here-document delimited by end-of-file ", 49);
	write(2, "(wanted '", 9);
	write(2, word, ft_strlen(word));
	write(2, "')\n", 3);
}
