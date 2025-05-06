/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:45:46 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 18:28:59 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_special(char c)
{
	return (c != '"' && c != '\'' &&
		c != '|' && c != '<' && c != '>');
}

static int is_space(char c)
{
	if(c == 32)
		return 1;
	else if (c >= 9 && c <=13)
		return 1;

	return 0;
}

int ft_is_empty(char *str)
{
	int i ;

	if(!str)
		return (0);

	i = -1;
	while(is_space(str[++i]))
	if(str[i] == '\0')
		return 1;
	return 0;
}

int ft_parsing(char *input, t_data *data)
{
	int i = 0;
	int start;
	char quote;
	t_token *token;


	while(input[i])
	{
		while(input[i] && is_space(input[i]))
			i++;
		if(!input[i])
			break;

		if(input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			i++;
			start = i;

			while(input[i] && input[i] != quote)
				i++;

			if(!input[i])
				return ft_print_error(data,
					"syntax error: unclosed quote\n", 258);

			token = ft_new_token(input + start, i - start, WORD);
			if(!token)
				return 1;
			ft_add_token(data, token);
			i++;

		}
		else
		{
			start = i;
			while(input[i] && !is_space(input[i]) && !is_special(input[i]))
				i++;
			if(i > start)
			{
				token = ft_new_token(input + start, i - start, WORD);
				if(!token)
					return 1;
				ft_add_token(data, token);
			}
		}

		
	}
	return 0;
}
