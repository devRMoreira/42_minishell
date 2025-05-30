/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:56 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/30 02:52:49 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_print_error(t_data *data, char *error, int exit_code)
{
	ft_printf("minishell: %s\n", error);
	data->exit_code = exit_code;
	return (exit_code);
}

int	ft_syntax_error(t_data *data, t_token *token)
{
	if (token == NULL)
		ft_print_error(data, "syntax error near unexpected token `newline'", 2);
	else if (token->type == PIPE)
		ft_print_error(data, "syntax error near unexpected token `|'", 2);
	else if (token->type == REDIRIN)
		ft_print_error(data, "syntax error near unexpected token `<'", 2);
	else if (token->type == REDIROUT)
		ft_print_error(data, "syntax error near unexpected token `>'", 2);
	else if (token->type == APPEND)
		ft_print_error(data, "syntax error near unexpected token `>>'", 2);
	else if (token->type == HEREDOC)
		ft_print_error(data, "syntax error near unexpected token `<<'", 2);
	else
		ft_print_error(data, "syntax error near unexpected token", 2);
	return (0);
}
