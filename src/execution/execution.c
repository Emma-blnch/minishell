/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:21 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/27 14:17:11 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

static void	parent_process(t_shell *shell, t_cmd *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = pip[0];
	if (cmd->next != shell->cmd && cmd->next->infile == -2)
		cmd->next->infile = pip[0];
	else
		close(pip[0]);
}

static bool	exec_cmd(t_shell *shell, t_cmd *cmd, int *pip)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all(shell, ERR_FORK, EXT_FORK);
	else if (!g_signal_pid)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(shell, cmd, pip);
		else
			free_all(shell, NULL, 0);
	}
	else
		parent_process(shell, cmd, pip);
	return (true);
}

static void	wait_all(t_shell *shell)
{
	int		status;
	int		pid;
	int		len;
	t_cmd	*tmp;

	tmp = shell->cmd;
	len = len_cmd(tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				g_signal_pid = WEXITSTATUS(status);
		}
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		if (tmp->infile >= 0)
			close(tmp->infile);
		tmp = tmp->next;
	}
}

int	exec_tree(t_shell *shell)
{
	t_cmd	*tmp;
	int		*pip;

	pip = shell->pip;
	tmp = shell->cmd;
	//printf("cmd_param:%s\n", tmp->cmd_param[0]);
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->cmd_param[0] \
		&& is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(shell, tmp));
	if (pipe(pip) == -1)
		return (false);
	exec_cmd(shell, tmp, pip);
	tmp = tmp->next;
	while (tmp != shell->cmd)
	{
		if (pipe(pip) == -1)
			return (-1);
		exec_cmd(shell, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(shell);
	return (true);
}
