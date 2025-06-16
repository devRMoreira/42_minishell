/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:57:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/06/16 13:50:23 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_syntax_check(t_data *data, char *input)
{
	int i = 0;
	char quote;

	while (input[i] && ft_is_space(input[i]))
		i++;

	if (input[i] == '|')
		return (ft_print_error(data, "syntax error near unexpected token `|'", 2), 0);

	while (input[i])
	{
		if(input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while(input[i] && input[i] != quote)
				i++;
			if(!input[i])
				return (ft_print_error(data, "syntax error: unclosed quote", 2), 0);
			i++;
			continue;
		}

		else if (input[i] == '|' && input[i + 1] == '|')
			return (ft_print_error(data, "syntax error near unexpected token `|'", 2), 0);

			else if (input[i] == '>' || input[i] == '<')
			{
				int len;
				int op = input[i];
				if(input[i + 1] == input[i])
				len = 2;
				else
				len = 1;
				i+=len;
				while (input[i] && ft_is_space(input[i]))
				i++;
				if(!input[i] || ft_is_operator(input[i]))
				{
					if(op == '>')
						return (ft_print_error(data, "syntax error near unexpected token `>'", 2), 0);
					else
						return (ft_print_error(data, "syntax error near unexpected token `<'", 2), 0);
				}
				continue;
			}
			i++;
		}

		i = ft_strlen(input) - 1;
		while (i >= 0 && ft_is_space(input[i]))
		i--;
		if (i >= 0 && input[i] == '|')
			return (ft_print_error(data, "syntax error near unexpected token `|'", 2), 0);

		return (1);
}
