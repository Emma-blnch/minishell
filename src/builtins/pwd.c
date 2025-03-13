/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:40 by skassimi          #+#    #+#             */
/*   Updated: 2025/03/13 11:11:05 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_pwd_option(char *opt)
{
	if (!opt)
		return (1);
	if (opt[0] == '-'
		&& ft_strncmp(opt, "-P", 3) != 0
		&& ft_strncmp(opt, "-L", 3) != 0
		&& ft_strncmp(opt, "-LP", 4) != 0
		&& ft_strncmp(opt, "-PL", 4) != 0)
		return (0);
	return (1);
}

static int	use_logical_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	pwd = getenv("PWD");
	if (!pwd)
		pwd = getcwd(cwd, PATH_MAX);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

static int	print_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	pwd(char **args)
{
	if (args[1])
	{
		if (!is_valid_pwd_option(args[1]))
		{
			printf("pwd: %s: invalid option\n", args[1]);
			printf("pwd: usage: pwd [-LP]\n");
			return (2);
		}
		if (args[2])
		{
			printf("pwd: too many arguments\n");
			return (1);
		}
		if (ft_strncmp(args[1], "-L", 3) == 0
			|| ft_strncmp(args[1], "-PL", 4) == 0)
			return (use_logical_pwd());
	}
	return (print_pwd());
}
