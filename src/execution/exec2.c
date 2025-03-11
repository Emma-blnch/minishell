/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:44:19 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/10 14:30:00 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dir(char **path, char *cmd, t_shell *shell)
{
	struct stat	path_stat;

	(void)shell;
	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error2(cmd);
		print_error2(" : Is a directory\n");
		g_signal_pid = 126;
		return (false);
	}
	return (true);
}

static bool	cmd_exist(char **path, t_shell *shell, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(cmd, shell->env);
	else
		absolute_path(path, cmd, shell);
	if (!(*path) && g_signal_pid == -1)
		free_all(shell, NULL, g_signal_pid);
	if (!(*path))
	{
		g_signal_pid = 127;
		return (false);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		g_signal_pid = 126;
		return (false);
	}
	if (!check_dir(path, cmd, shell))
		return (false);
	return (true);
}

static void	redirect_in_out(t_shell *shell, t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != shell->cmd)
		dup2(pip[1], 1);
	close(pip[1]);
}

static void	built(int *pip, t_cmd *cmd, t_shell *shell)
{
	close(pip[0]);
	if (cmd->outfile < 0 && cmd->next != shell->cmd)
		cmd->outfile = pip[1];
	else
		close(pip[1]);
	launch_builtin(shell, cmd);
}

void	child_process(t_shell *shell, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**env;

	path = NULL;
	if (cmd->skip_cmd)
		g_signal_pid = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		built(pip, cmd, shell);
	else if (cmd_exist(&path, shell, cmd->cmd_param[0]))
	{
		redirect_in_out(shell, cmd, pip);
		env = lst_to_arr(shell->env);
		if (!env)
			free_all(shell, ERR_MALLOC, EXT_MALLOC);
		rl_clear_history();
		execve(path, cmd->cmd_param, env);
		free(env);
	}
	if (path)
		free(path);
	free_all(shell, NULL, g_signal_pid);
}
