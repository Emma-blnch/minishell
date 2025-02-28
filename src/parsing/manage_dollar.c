/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:15:25 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/28 13:47:53 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_point_interrogation(t_shell *shell, char **str)
{
	char	*tmp;
	char	*tmp2;

	(void)shell;
	tmp = ft_itoa(g_signal_pid);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

int	add_dollar(char *line, int *index, char **str, t_shell *shell)
{
	int		ctrl;
	int		n;

	n = *index;
	ctrl = exist_in_env(line, index, shell);
	if (ctrl == 1)
		return (in_env(shell, &line[n], *index - n, str));
	else if (ctrl == 2)
	{
		(*index) += 2;
		return (dollar_point_interrogation(shell, str));
	}
	else
	{
		++(*index);
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			++(*index);
		return (1);
	}
}

int	add_char(char *c, char **str, t_shell *shell, int *index)
{
	char	char_to_str[2];
	char	*tmp2;
	int		i;

	i = 0;
	if (c[i] == '$' && !shell->squote && exist_in_env(c, &i, shell))
		return (1);
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp2 = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

static int	process_dollar(char **line, t_shell *shell, char **str)
{
	int		i;
	bool	dq;

	i = 0;
	dq = false;
	shell->squote = false;
	while ((*line)[i])
	{
		quoting_choice(&dq, &shell->squote, NULL, (*line)[i]);
		if ((*line)[i] == '$' && !shell->squote &&
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?'
			|| (*line)[i + 1] == '_'))
		{
			if (!add_dollar((*line), &i, str, shell))
				return (0);
		}
		else
		{
			if (!add_char(&(*line)[i], str, shell, &i))
				return (0);
		}
	}
	return (1);
}

int	replace_dollar(char **line, t_shell *shell)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (0);
	if (!process_dollar(line, shell, &str))
		return (0);
	free(*line);
	*line = str;
	return (1);
}
