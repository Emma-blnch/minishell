/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:30 by skassimi          #+#    #+#             */
/*   Updated: 2025/03/13 11:40:59 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_shell *shell)
{
	t_list	*tmp;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	tmp = shell->env;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (error_malloc());
	export2(oldpwd, &shell->env);
	free(oldpwd);
}

static void	update_pwd(t_shell *shell, char *param)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(shell);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export2(pwd, &shell->env);
	free(pwd);
}

static char	*get_target_path(t_shell *shell, char **params, bool *allocated)
{
	char	*path;

	*allocated = false;
	if (count_arg(params) == 1
		|| (count_arg(params) == 2 && !ft_strncmp(params[1], "~", 2)))
	{
		path = get_elem_env(shell->env, "HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		*allocated = true;
	}
	else if (count_arg(params) == 2)
		path = params[1];
	else
		path = NULL;
	return (path);
}

static int	exec_cd(t_shell *shell, char *path)
{
	int	res;

	res = chdir(path);
	if (res == 0)
		update_pwd(shell, path);
	if (res == -1)
	{
		perror(path);
		return (1);
	}
	return (0);
}

int	cd(t_shell *shell, char **params)
{
	char	*path;
	bool	allocated;
	int		res;

	if (params[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	path = get_target_path(shell, params, &allocated);
	if (!path)
		return (1);
	res = exec_cd(shell, path);
	if (allocated)
		free(path);
	return (res);
}
