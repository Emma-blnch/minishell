/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:37:18 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/27 14:17:08 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_new_elem(t_cmd **new, int infile, int outfile, char **cmd_param)
{
	(*new) = malloc(sizeof(t_cmd));
	if (*new == NULL)
		return (0);
	(*new)->skip_cmd = false;
	(*new)->infile = infile;
	(*new)->outfile = outfile;
	(*new)->cmd_param = cmd_param;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param)
{
	t_cmd	*new;

	if (!cmd_new_elem(&new, infile, outfile, cmd_param))
		return (0);
	if (!(*list))
	{
		(*list) = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

static bool	fill_cmd(t_shell *shell, t_token *tmp)
{
	if (!get_infile(shell, tmp, shell->cmd->prev) && \
		shell->cmd->prev->infile != -1)
		return (false);
	if (shell->cmd->prev->infile == -1)
	{
		shell->cmd->prev->skip_cmd = true;
		shell->cmd->prev->outfile = -1;
		return (true);
	}
	if (!get_outfile(tmp, shell->cmd->prev, shell) && shell->cmd->prev->outfile \
		!= -1)
		return (false);
	if (shell->cmd->prev->outfile == -1)
	{
		if (shell->cmd->prev->infile >= 0)
			close (shell->cmd->prev->infile);
		shell->cmd->prev->skip_cmd = true;
		shell->cmd->prev->infile = -1;
		return (true);
	}
	shell->cmd->prev->cmd_param = get_param(shell, tmp);
	if (!shell->cmd->prev->cmd_param)
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
	return (true);
}

static bool	norm(t_shell *shell, t_token *tmp)
{
	if (!append_cmd(&shell->cmd, -2, -2, NULL))
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
	if (!fill_cmd(shell, tmp))
	{
		g_signal_pid = 2;
		return (false);
	}
	return (true);
}

bool	create_list_cmd(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	if (!norm(shell, tmp))
		return (false);
	tmp = tmp->next;
	while (tmp !=shell->token)
	{
		if (tmp->prev->type == PIPE)
		{
			if (!norm(shell, tmp))
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
