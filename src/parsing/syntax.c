/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:57:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/08 10:01:28 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_quote(char *input, int *i, t_data *data)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (ft_print_error(data, "syntax error: unclosed quote", 2), 0);
	(*i)++;
	return (1);
}

static int	skip_redir_quote(char *input, int *i, t_data *data)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (ft_print_error(data, "syntax error: unclosed quote", 2), 0);
	(*i)++;
	return (1);
}

static int	check_redir(t_data *data, char *input, int *i)
{
	int	len;

	len = 1;
	if (input[*i + 1] == input[*i])
		len = 2;
	*i += len;
	while (input[*i] && ft_is_space(input[*i]))
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (!skip_redir_quote(input, i, data))
			return (0);
	}
	else if (!input[*i])
		return (ft_print_error(data,
				"syntax error near unexpected token `newline'", 2), 0);
	else if (ft_is_operator(input[*i]))
	{
		if (input[*i] == '>')
		{
			if (input[*i + 1] == '>')
				return (ft_print_error(data,
						"syntax error near unexpected token `>>'", 2), 0);
			else
				return (ft_print_error(data,
						"syntax error near unexpected token `>'", 2), 0);
		}
		else if (input[*i] == '<')
		{
			if (input[*i + 1] == '<')
				return (ft_print_error(data,
						"syntax error near unexpected token `<<'", 2), 0);
			else
				return (ft_print_error(data,
						"syntax error near unexpected token `<'", 2), 0);
		}
		else if (input[*i] == '|')
			return (ft_print_error(data,
					"syntax error near unexpected token `|'", 2), 0);
		else
			return (ft_print_error(data,
					"syntax error near unexpected token", 2), 0);
	}
	return (1);
}

static int	syntax_check_loop(t_data *data, char *input, int *i)
{
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quote(input, i, data))
				return (0);
			continue ;
		}
		else if (input[*i] == '|' && input[*i + 1] == '|')
			return (ft_print_error(data,
					"syntax error near unexpected token `|'", 2), 0);
		else if (input[*i] == '>' || input[*i] == '<')
		{
			if (!check_redir(data, input, i))
				return (0);
			continue ;
		}
		(*i)++;
	}
	return (1);
}

int	ft_syntax_check(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (input[i] == '|')
		return (ft_print_error(data,
				"syntax error near unexpected token `|'", 2), 0);
	if (!syntax_check_loop(data, input, &i))
		return (0);
	if (!ft_check_pipe_end(data, input))
		return (0);
	return (1);
}
