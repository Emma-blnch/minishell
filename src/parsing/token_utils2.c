/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:29:21 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 09:38:42 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_syntax_error(t_token **begin)
{
	write(2, "syntax error near unexpected token `>>'\n", 41);
	free_token(begin);
	return (false);
}

bool	handle_special_token(t_token **begin, char **command,
		int *last_was_operator)
{
	if (*last_was_operator)
		return (handle_syntax_error(begin));
	if (!add_special(begin, command))
	{
		free_token(begin);
		return (false);
	}
	*last_was_operator = 1;
	return (true);
}

bool	handle_command_token(t_token **begin, char **command,
		int *last_was_operator)
{
	if (!add_cmd(begin, command))
	{
		free_token(begin);
		return (false);
	}
	*last_was_operator = 0;
	return (true);
}
