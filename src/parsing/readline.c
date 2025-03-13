/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:49:13 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/13 09:25:39 by ahamini          ###   ########.fr       */
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

bool	check_syntax(char *input)
{
	t_token	*tmp_token;

	tmp_token = NULL;
	if (!create_list_token(&tmp_token, input))
	{
		free_token(&tmp_token);
		return (false);
	}
	free_token(&tmp_token);
	return (true);
}

bool	parse_cmd(t_shell *shell, char *input)
{
	if (!handle_quotes_and_dollar(shell, input))
		return (false);
	if (!handle_syntax_and_replacement(shell, &input))
		return (false);
	if (!handle_token_and_malloc(shell, input))
		return (false);
	if (!handle_cmd_list(shell))
		return (false);
	return (check_pipe(shell));
}

int	init_readline(t_shell *shell)
{
	char	*input;

	while (1)
	{
		signals();
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
	}
	rl_clear_history();
	free_all(shell, NULL, -1);
	return (0);
}
