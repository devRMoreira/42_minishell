/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:07:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/05 15:53:15 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	total_tokens(t_token *tokens)
{
	int	res;

	res = 0;
	while (tokens && tokens->type == WORD)
	{
		res++;
		tokens = tokens->next;
	}
	return (res);
}

char	**ft_build_argv(t_token *tokens)
{
	int		i;
	int		argc;
	char	**argv;
	t_token	*temp;

	argc = total_tokens(tokens);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	temp = tokens;
	i = 0;
	while (temp && temp->type == WORD)
	{
		argv[i] = ft_strdup(temp->input);
		if (!argv[i])
			return (ft_free_split(argv), NULL);
		temp = temp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static void	write_free(char *line, char *expanded, int write_fd)
{
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(line);
	free(expanded);
}

int	ft_handle_heredoc(char *delim, t_data *data)
{
	int		pipe_fd[2];
	char	*line;
	char	*expanded_line;

	if (pipe(pipe_fd) == -1)
		return (ft_print_error(data, "pipe failed", 1), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_print_error(data,
				"warning: here-document delimited by end-of-file", 0);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = ft_expand(data, line);
		write_free(line, expanded_line, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	ft_has_pipes(t_cmd *cmds)
{
	t_cmd	*temp;

	temp = cmds;
	while (temp)
	{
		if (temp->next)
			return (1);
		temp = temp->next;
	}
	return (0);
}
