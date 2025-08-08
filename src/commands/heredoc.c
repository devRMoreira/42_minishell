/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:30:00 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/08 09:36:46 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	write_free(char *line, char *expanded, int write_fd)
{
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(line);
	free(expanded);
}

static char	*handle_heredoc_expansion(t_data *data, char *str,
										int *i, char *res)
{
	int		start;
	char	*temp;
	char	*segment;
	char	*expand;

	if (str[*i] == '$')
	{
		if (str[*i + 1] == '\'')
		{
			(*i) += 2;
			start = *i;
			while (str[*i] && str[*i] != '\'')
				(*i)++;
			temp = ft_substr(str, start, *i - start);
			if (!temp)
				return (free(res), NULL);
			segment = ft_strjoin(res, temp);
			free(temp);
			free(res);
			if (str[*i] == '\'')
				(*i)++;
			return (segment);
		}
		expand = ft_expand_var(data, str, i);
		segment = ft_strjoin(res, expand);
		free(res);
		free(expand);
		return (segment);
	}
	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	if (!temp)
		return (free(res), NULL);
	segment = ft_strjoin(res, temp);
	free(temp);
	free(res);
	return (segment);
}

char	*ft_expand_heredoc(t_data *data, char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[i])
	{
		res = handle_heredoc_expansion(data, str, &i, res);
	}
	return (res);
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
		expanded_line = ft_expand_heredoc(data, line);
		write_free(line, expanded_line, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
