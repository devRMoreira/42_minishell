/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:57:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/11 16:52:32 by rimagalh         ###   ########.fr       */
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

/* Simple syntax check loop that validates quotes and double pipes */
static int	syntax_check_loop(t_data *data, char *input, int *i)
{
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quote(input, i, data))
				return (0);
		}
		else if (input[*i] == '|' && input[*i + 1] == '|')
			return (ft_print_error(data,
					"syntax error near unexpected token `|'", 2), 0);
		else
			(*i)++;
	}
	return (1);
}

/*
** Simplified syntax check that only validates essential syntax:
** - Unclosed quotes (must be caught early, can't be tokenized)
** - Leading pipe (invalid in bash)
** - Trailing pipe (invalid in bash)
** Complex syntax validation is handled by the tokenizer and parser.
*/
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
