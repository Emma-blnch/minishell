/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:30 by ahamini           #+#    #+#             */
/*   Updated: 2025/03/11 13:54:43 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void write_eof(char *word)
{
    write(2, "warning: here-document delimited by end-of-file ", 49);
    write(2, "(wanted '", 9);
    write(2, word, ft_strlen(word));
    write(2, "')\n", 3);
}

static bool    read_in_stdin(t_shell *shell, int fd, char *word)
{
    char    *buf;

    signal(SIGINT, SIG_DFL);
    while (1)
    {
        buf = readline("> ");
        if (!buf)
        {
            write_eof(word);
            break ;
        }
        if (!ft_strncmp(word, buf, INT_MAX))
        {
            free(buf);
            break ;
        }
        if (!replace_dollar(&buf, shell))
            free_all(shell, ERR_MALLOC, EXT_MALLOC);
        write(fd, buf, ft_strlen(buf));
        write(fd, "\n", 1);
        free(buf);
    }
    close(fd);
    return (true);
}

static void    handle_sigint_heredoc(t_shell *shell, int pipefd[2])
{
    write(1, "\n", 1);
    clear_rl_line();
    rl_on_new_line();
    shell->heredoc_interrupted = true;
    g_signal_pid = 130;
    close(pipefd[0]);
}

int    here_doc(t_shell *shell, char *word)
{
    int        pid;
    int        status;
    int        pipefd[2];

	signal(SIGINT, SIG_IGN);
    if (pipe(pipefd) == -1)
        return (-1);
    pid = fork();
    if (pid < 0)
        return (-1);
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        close(pipefd[0]);
        if (!read_in_stdin(shell, pipefd[1], word))
            exit(1);
        exit(0);
    }
    else
    {
        close(pipefd[1]);
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            g_signal_pid = 130;
            return (handle_sigint_heredoc(shell, &pipefd[0]), -1);
        }
        return (pipefd[0]);
    }
}
