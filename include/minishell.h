/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:10 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 16:08:52 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
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


int ft_is_empty(char *str);
int ft_parsing(char *input, t_data data);


#endif
