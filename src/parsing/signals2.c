/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:29:32 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/28 11:45:18 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	handle_sigtstp(int code)
{
	(void)code;
	if (g_signal_pid > 0)
	{
		printf("\n[Minishell] Processus suspendu : %d\n", g_signal_pid);
		kill(g_signal_pid, SIGSTOP);
		clear_rl_line();
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		clear_rl_line();
		printf("\n[Minishell] Ignore CTRL+Z\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}
