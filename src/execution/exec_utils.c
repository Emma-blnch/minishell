/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:16:24 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 10:19:02 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	absolute_path(char **path, char *cmd, t_shell *shell)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
	if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

void	handle_status(t_shell *shell, int status)
{
	int	sig;

	if (shell->heredoc_interrupted)
	{
		shell->heredoc_interrupted = false;
		g_signal_pid = 130;
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			g_signal_pid = 130;
		}
	}
	else if (WIFEXITED(status))
		g_signal_pid = WEXITSTATUS(status);
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	if (cmd->infile >= 0)
		close(cmd->infile);
}
