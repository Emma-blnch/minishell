/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:02:49 by skassimi          #+#    #+#             */
/*   Updated: 2025/03/13 11:11:20 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "/home/ahamini/Documents/minishell2/inc/libft/inc/libft.h"
//# include "/home/akim/42/minishell/inc/libft/inc/libft.h"

extern pid_t	g_signal_pid;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_shell
{
	t_list			*env;
	t_token			*token;
	t_cmd			*cmd;
	pid_t			pid;
	int				exit_code;
	int				pip[2];
	int				std_in;
	int				std_out;
	int				ret;	
	bool			squote;
	bool			heredoc_interrupted;
	char			**paths;
	char			**envp;
}				t_shell;

/* INPUT */

bool		parse_cmd(t_shell *shell, char *input);
void		extract_env_as_linked_list(t_shell *shell);
int			extract_paths(t_shell *shell);
int			init_readline(t_shell *shell);
bool		empty_input(char *line);

/* PARSING */

int			create_minishell(t_shell *shell, char **envp);
bool		is_space(char c);
int			open_quote(t_shell *shell, char *input);
void		quoting_choice(bool *d_quote, bool *s_quote, int *index, char c);
int			replace_dollar(char **line, t_shell *shell);
int			check_double_dollar(char *line);
bool		check_syntax(char *input);
int			add_char(char *c, char **str, t_shell *shell, int *index);
int			add_dollar(char *line, int *index, char **str, t_shell *shell);
char		*get_dollar_word(char *line, int size);
char		*get_elem_env(t_list *env, char *key);
int			in_env(t_shell *shell, char *line, int size, char **str);
int			exist_in_env(char *line, int *i, t_shell *shell);
size_t		len_list(t_list *list);
bool		create_list_token(t_token **begin, char *command);
bool		create_list_cmd(t_shell *shell);
bool		handle_cmd_list(t_shell *shell);
bool		handle_token_and_malloc(t_shell *shell, char *input);
bool		handle_syntax_and_replacement(t_shell *shell, char **input);
bool		handle_quotes_and_dollar(t_shell *shell, char *input);
bool		handle_command_token(t_token **begin, char **command,
				int *last_was_operator);
bool		handle_special_token(t_token **begin, char **command,
				int *last_was_operator);
bool		add_special(t_token **begin, char **command);
bool		add_cmd(t_token **begin, char **command);
bool		handle_syntax_error(t_token **begin);
bool		is_space(char c);
int			is_special(char *str);
int			append_token(t_token **list, char *str, int type);
int			append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param);
bool		get_outfile(t_token *token, t_cmd *cmd, t_shell *shell);
bool		get_infile(t_shell *shell, t_token *token, t_cmd *cmd);
char		**get_param(t_shell *shell, t_token *token);

/* HEREDOC */

int			here_doc(t_shell *shell, char *word);
void		write_eof(char *word);

/* EXECUTION */

int			exec_tree(t_shell *shell);
void		close_fds(t_cmd *cmd);
void		handle_status(t_shell *shell, int status);
int			append(t_list **list, char *elem);
char		**lst_to_arr(t_list *env);
void		child_process(t_shell *shell, t_cmd *cmd, int *pip);
void		absolute_path(char **path, char *cmd, t_shell *shell);
char		*find_cmd(char *sample, t_list *env);
void		add_first2(t_list **list, t_list *new);

/* BUILT IN */

int			cd(t_shell *shell, char **params);
int			count_arg(char **params);
void		error_malloc(void);
int			echo(char **argv);
int			env(t_list *env, char **cmd);
int			export(char **str, t_list **env);
bool		export2(char *str, t_list **env);
void		sort_array(char **arr, int len);
int			ft_unset(char **str, t_list **env);
t_list		*find_env(t_list *env_list, char *env_name);
int			pwd(char **args);
void		ft_exit(t_shell *shell, char **args);
int			launch_builtin(t_shell *shell, t_cmd *cmd);
int			is_builtin(char *cmd);

/* ERROR HANDLING */

void		set_error_if(int cond, int err_code, t_shell *shell, char *message);
void		set_error(int err_code, t_shell *shell, char *err_message);
void		set_cmd_error(int err_code, t_cmd *cmd, char *err_message);
void		print_error(void);
bool		print_error_token(t_token *token, t_shell *shell);
bool		print_error2(char *str);

/* CLEAN UP */

void		free_all(t_shell *shell, char *err, int ext);
void		free_cmd(t_cmd **list);
void		free_array(char **arr);
void		free_token(t_token **list);
int			free_list(t_list **list);

/* SIGNALS */

void		clear_rl_line(void);
void		signals(void);
void		handle_sigtstp(int code);
void		handle_sigint(int code);
void		signals2(void);

/* DEBUG */

void		print_tokens(t_list *first);

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"
# define ENV		8

# define ERR_MALLOC	"malloc error\n"
# define ERR_PIPE	"pipe error\n"
# define ERR_FORK	"fork error\n"
# define SHELL_NAME	"shell"

# define EXT_MALLOC		1
# define EXT_PIPE		1
# define EXT_FORK		1
# define MALLOC_FAIL	1
# define DEFAULT_PATH "PATH=/usr/bin"

#endif
