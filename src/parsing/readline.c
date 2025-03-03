/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:49:13 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/03 14:11:12 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n", tmp->type, tmp->str);
}*/

static int	check_double_dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '$')
		{
			ft_putstr_fd("PID: command not found\n", 2);
			g_signal_pid = 127;
			return (1);
		}
		i++;
	}
	return (0);
}

bool	check_pipe(t_shell *shell)
{
	if (shell->token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&shell->token);
		free_cmd(&shell->cmd);
		return (false);
	}
	return (true);
}

bool	empty_input(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	parse_cmd(t_shell *shell, char *input)
{
	if (open_quote(shell, input))
	{
		free(input);
		return (false);
	}
	if (check_double_dollar(input))
	{
		free(input);
		return (false);
	}
	if (!replace_dollar(&input, shell)
		|| !create_list_token(&shell->token, input))
	{
		free(input);
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
		return (false);
	}
	free(input);
	//print_token(shell->token);
	if (!shell->token || !create_list_cmd(shell))
	{
		free_token(&shell->token);
		free_cmd(&shell->cmd);
		return (false);
	}
	return (check_pipe(shell));
}

int	init_readline(t_shell *shell)
{
	char		*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			free_all(shell, "exit\n", g_signal_pid);
		if (empty_input(input))
			continue ;
		add_history(input);
		if (!parse_cmd(shell, input))
			continue ;
		if (!exec_tree(shell))
			free_all(shell, ERR_PIPE, EXT_PIPE);
		free_cmd(&shell->cmd);
		free_token(&shell->token);
		//g_signal_pid = 0;
	}
	rl_clear_history();
	free_all(shell, NULL, -1);
	return (0);
}
