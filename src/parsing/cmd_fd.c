/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:44:21 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/28 11:30:09 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_shell *shell, char *filename, int type)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = here_doc(shell, filename);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

static bool	get_in(t_shell *shell, t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == INPUT)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, shell));
		cmd->infile = open_file(shell, tmp->next->str, INPUT);
		if (cmd->infile == -1)
			return (false);
	}
	else if (tmp->type == HEREDOC)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, shell));
		cmd->infile = open_file(shell, tmp->next->str, HEREDOC);
		if (cmd->infile == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_shell *shell, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_in(shell, tmp, cmd))
		return (false);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp->type != PIPE && tmp != shell->token)
	{
		if (!get_in(shell, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

static bool	get_out(t_token *tmp, t_cmd *cmd, t_shell *shell)
{
	if (tmp->type == TRUNC)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, shell));
		cmd->outfile = open_file(NULL, tmp->next->str, TRUNC);
		if (cmd->outfile == -1)
			return (false);
	}
	else if (tmp->type == APPEND)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, shell));
		cmd->outfile = open_file(NULL, tmp->next->str, APPEND);
		if (cmd->outfile == -1)
			return (false);
	}
	return (true);
}

bool	get_outfile(t_token *token, t_cmd *cmd, t_shell *shell)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_out(tmp, cmd, shell))
		return (false);
	tmp = tmp->next;
	while (tmp != shell->token && tmp->type != PIPE)
	{
		if (!get_out(tmp, cmd, shell))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
