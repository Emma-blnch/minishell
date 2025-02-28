/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:20:16 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/28 11:08:32 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	almost_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

void	ft_exit(t_shell *shell, char **args)
{
	int	err;

	err = 0;
	printf("exit\n");
	if (args[1])
	{
		shell->ret = almost_atoi(args[1], &err);
		if (err)
		{
			print_error2("exit: ");
			print_error2(args[1]);
			print_error2(": numeric argument required\n");
			free_all(shell, NULL, 2);
		}
	}
	if (args[1] && args[2])
	{
		print_error2("exit: too many arguments\n");
		g_signal_pid = 1;
		return ;
	}
	if (!args[1])
		free_all(shell, NULL, g_signal_pid);
	free_all(shell, NULL, shell->ret);
}
