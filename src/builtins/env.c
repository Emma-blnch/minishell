/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:20:08 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/27 11:20:16 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_env_as_linked_list(t_shell *shell)
{
	int		index;

	index = 0;
	while (shell->envp[index])
	{
		ft_lstadd_back(&shell->env,
			ft_lstnew(ft_strdup(shell->envp[index])),ENV);
		index++;
	}
}

int	env(t_list *env, char **cmd)
{
	t_list	*temp;

	temp = env;
	if (cmd[1])
	{
		print_error2("env: too many arguments\n");
		return (1);
	}
	if (!temp)
		return (0);
	if (ft_strchr(temp->str, '='))
		printf("%s\n", temp->str);
	temp = temp->next;
	while (temp != env)
	{
		if (ft_strchr(temp->str, '='))
			printf("%s\n", temp->str);
		temp = temp->next;
	}
	return (0);
}
