/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:10 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/05 15:56:52 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRIN,
	REDIROUT,
	HEREDOC,
	APPEND
}	t_token_type;

typedef struct s_token
{
	char			*input;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	int				pipe[2];
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*input;
	char	**envp;
	int		exit_code;
	t_token	*tokens;
	t_cmd	*cmds;

}	t_data;

int				ft_is_builtin(char *cmd);
int				ft_exec_builtin(char **argv, t_data *data);
int				ft_cd(char **argv, t_data *data);
int				ft_echo(char **argv);
void			ft_exec_pipes(t_data *data);
int				ft_exit(char **argv, t_data *data);
char			*ft_expand(t_data *data, char *str);
int				ft_env(t_data *data);
char			*ft_strjoin_3(char *str1, char *str2, char *str3);
int				ft_pwd(char **argv, t_data *data);
int				ft_handle_heredoc(char *delim, t_data *data);
void			ft_exec_cmds(t_data *data);
int				ft_has_pipes(t_cmd *cmds);
void			ft_close_pipes(t_cmd *cmds);
void			ft_handle_sigint(int sig);
int				ft_check_path(char **argv, t_data *data, char **path);
char			**ft_build_argv(t_token *tokens);
t_data			*ft_init_data(char **envp);
int				ft_parsing(char *input, t_data *data);
char			*ft_expand_var(t_data *data, char *str, int *i);
int				ft_syntax_check(t_data *data, char *input);
int				ft_print_error(t_data *data, char *error, int exit_code);
int				ft_syntax_error(t_data *data, t_token *token);
t_token			*ft_new_token(char *str, int length, t_token_type type);
int				ft_set_env(t_data *data, char *key, char *value);
char			*ft_get_env(t_data *data, char *val);
void			ft_add_token(t_data *data, t_token *token);
int				ft_parse_cmds(t_data *data);
char			*ft_expand_var(t_data *data, char *str, int *i);
void			ft_free_tokens(t_token *tokens);
void			ft_clean_cmds(t_data *data);
void			ft_free_data(t_data *data);
void			ft_free_cmds(t_cmd *cmds);
void			ft_free_split(char **paths);
t_cmd			*ft_new_cmd(void);
char			*ft_create_word(char *str1, char *str2);
int				ft_is_empty(char *s);
int				ft_is_space(char c);
int				ft_is_operator(char c);
t_token_type	ft_get_operator_type(char c, char next);
int				ft_check_pipe_end(t_data *data, char *input);
int				ft_export(char **argv, t_data *data);
int				ft_unset(char **argv, t_data *data);
void			ft_print_env(t_data *data);

#endif
