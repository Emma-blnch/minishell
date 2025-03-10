/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:48:17 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/10 12:10:32 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_new_elem_str(t_list **new, char *elem)
{
	(*new) = malloc(sizeof(t_list));
	if (*new == NULL)
		return (0);
	(*new)->str = elem;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

static void	add_first(t_list **list, t_list *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	append(t_list **list, char *elem)
{
	t_list	*new;

	if (!list_new_elem_str(&new, elem))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

bool    make_env(t_shell *shell)
{
    char    path[PATH_MAX];
    char    *tmp;

    tmp = ft_strdup("OLDPWD");
    if (!tmp || !append(&(shell->env), tmp) || getcwd(path, PATH_MAX) == NULL)
        free_all(shell, ERR_MALLOC, EXT_MALLOC);
    tmp = ft_strjoin("PWD=", path);
    if (!tmp || !append(&(shell->env), tmp))
        free_all(shell, ERR_MALLOC, EXT_MALLOC);
    tmp = ft_strdup(DEFAULT_PATH);
    if (!tmp || !append(&(shell->env), tmp))
        free_all(shell, ERR_MALLOC, EXT_MALLOC);
    return (1);
}

static int    has_env_key(t_list *env, const char *key)
{
    t_list    *tmp;
    size_t    len;

    if (!env)
        return (0);
    len = ft_strlen(key);
    tmp = env;
    while (1)
    {
        if (!ft_strncmp(tmp->str, key, len) && tmp->str[len] == '=')
            return (1);
        tmp = tmp->next;
        if (tmp == env)
            break;
    }
    return (0);
}

int    create_minishell(t_shell *shell, char **env)
{
    t_list    *list;
    int        i;
    char    *tmp;

    if (!(*env))
        return (make_env(shell));
    i = -1;
    list = NULL;
    while (env[++i])
    {
        tmp = ft_strdup(env[i]);
        if (!tmp)
            return (free_list(&list));
        if (!append(&list, tmp))
            return (free_list(&list));
    }
    shell->env = list;
    if (!has_env_key(shell->env, "PATH"))
    {
        tmp = ft_strdup(DEFAULT_PATH);
        if (!tmp || !append(&shell->env, tmp))
            return (free_list(&shell->env));
    }
    return (1);
}
