/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:50:04 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 11:11:54 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc >= 2)
	{
		printf("Usage : './minishell'\n");
		return (0);
	}
	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.token = NULL;
	shell.cmd = NULL;
	shell.exit_code = 0;
	shell.pip[0] = -1;
	shell.pip[1] = -1;
	shell.ret = 0;
	g_signal_pid = 0;
	if (!create_minishell(&shell, envp))
		free_all(&shell, ERR_MALLOC, EXT_MALLOC);
	init_readline(&shell);
	return (0);
}
