/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:46:35 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 10:58:27 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(int save_stdout, t_shell *shell, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd_param[0], INT_MAX))
		g_signal_pid = echo(cmd->cmd_param);
	else if (!ft_strncmp("cd", cmd->cmd_param[0], INT_MAX))
		g_signal_pid = cd(shell, cmd->cmd_param);
	else if (!ft_strncmp("pwd", cmd->cmd_param[0], INT_MAX))
		g_signal_pid = pwd(cmd->cmd_param);
	else if (!ft_strncmp("export", cmd->cmd_param[0], INT_MAX))
		g_signal_pid = export(cmd->cmd_param, &shell->env);
	else if (!ft_strncmp("unset", cmd->cmd_param[0], INT_MAX))
		g_signal_pid = ft_unset(cmd->cmd_param, &shell->env);
	else if (!ft_strncmp("env", cmd->cmd_param[0], INT_MAX))
		g_signal_pid = env(shell->env, cmd->cmd_param);
	else if (!ft_strncmp("exit", cmd->cmd_param[0], INT_MAX))
	{
		if (cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(shell, cmd->cmd_param);
	}
}

int	launch_builtin(t_shell *shell, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	exec_builtin(save_stdout, shell, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close (save_stdout);
	}
	return (true);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX) || !ft_strncmp("cd", cmd, INT_MAX) \
	|| !ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("export", cmd, INT_MAX) \
	|| !ft_strncmp("unset", cmd, INT_MAX) || !ft_strncmp("env", cmd, INT_MAX) \
	|| !ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}
