/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:20:01 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 09:27:41 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_quotes_and_dollar(t_shell *shell, char *input)
{
	if (open_quote(shell, input) || check_double_dollar(input))
	{
		free(input);
		return (false);
	}
	return (true);
}

bool	handle_syntax_and_replacement(t_shell *shell, char **input)
{
	if (!check_syntax(*input) || !replace_dollar(input, shell))
	{
		free(*input);
		return (false);
	}
	return (true);
}

bool	handle_token_and_malloc(t_shell *shell, char *input)
{
	if (!create_list_token(&shell->token, input))
	{
		free(input);
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
		return (false);
	}
	free(input);
	return (true);
}

bool	handle_cmd_list(t_shell *shell)
{
	if (!shell->token || !create_list_cmd(shell))
	{
		free_token(&shell->token);
		free_cmd(&shell->cmd);
		return (false);
	}
	return (true);
}
