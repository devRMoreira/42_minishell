/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:10 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/12 17:57:28 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
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
} t_token_type;

typedef struct s_token
{
	char *input;
	t_token_type type;
	struct s_token *next;
} t_token;

typedef struct s_cmd
{
	char **argv;
	char *path;
	int pipe[2];
	int input_fd;
	int output_fd;
	struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
	char *input;
	char **envp;
	int exit_status;
	t_token *tokens;
	t_cmd *cmds;

}	t_data;

void ft_execute_command(char **argv, t_data *data);
char **ft_build_argv(t_token *tokens);
t_data *ft_init_data(char **envp);
void ft_free_tokens(t_token *tokens);
int ft_parsing(char *input, t_data *data);
int ft_print_error(t_data *data, char* error, int exit_code);
t_token *ft_new_token(char *str, int length, t_token_type type);
char *ft_get_env_var(t_data *data, const char *val);
void ft_add_token(t_data *data, t_token *token);
void ft_free_data(t_data *data);
void ft_free_split(char **paths);
void ft_free_argv(char **argv);




#endif
