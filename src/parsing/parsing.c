/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:45:46 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/16 12:20:44 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
static int is_empty(char *s)
{
	int i = -1;

	while(is_space(s[++i]));
	if(!s[i])
		return 1;
	return 0;
}

static t_token_type get_operator_type(char c, char next)
{
	if (c == '|' && next != '|')
	return PIPE;
	if (c == '<' && next == '<')
		return HEREDOC;
	if (c == '<')
		return REDIRIN;
	if (c == '>' && next == '>')
		return APPEND;
	if (c == '>')
		return REDIROUT;
	return WORD;
	//! fallback just in case
}

int ft_parsing(char *input, t_data *data)
{
	int i = 0;
	int start;
	char quote;
	t_token *token;

	if(is_empty(input))
		return 0;

	while(input[i])
	{
		//! skipping leading spaces
		while(input[i] && is_space(input[i]))
			i++;

		if(!input[i])
			break;
		//if its an operator <>|
		if (is_operator(input[i]))
		{

			//we find the op type and make it into a new token
			t_token_type type = get_operator_type(input[i], input[i+1]);
			int len;
			if(type == HEREDOC || type == APPEND)
				len = 2;
			else
				len = 1;

			token = ft_new_token(input + i, len, type);
			if(!token)
				return 0;
			ft_add_token(data, token);
			i += len;
		}
		//otherwise its just a regular char
		else
		{
			start = i;
			//and while its not a space or anything important we skip it
			while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
			{
				// if we find a quote
				if(input[i] == '"' || input[i] == '\'')
				{
					// hold it and skip to next
					quote = input[i++];
					//while its not over and it's not the quote char i++
					while(input[i] && input[i] != quote)
						i++;
					//if end of word, it didn't find a matching
					if(!input[i])
						return ft_print_error(data, "syntax error: unclosed quote\n", 258);

				}
				i++;
			}
			//turn it into a new token
			token = ft_new_token(input + start, i - start, WORD);
			if(!token)
				return 0;
			ft_add_token(data, token);
		}


	}
	return 1;
}


//! old quote if on parsing

//* if quotes
// if(input[i] == '"' || input[i] == '\'')
// {
// 	quote = input[i];
// 	i++;
// 	start = i;

//* find matching quote
// 	while(input[i] && input[i] != quote)
// 		i++;
//* if not found error
// 	if(!input[i])
// 		return ft_print_error(data, "syntax error: unclosed quote\n", 258);

//* 	else it creates a new token with the inbetween quotes
// 	token = ft_new_token(input + start, i - start, WORD);
// 	if(!token)
// 		return 0;
// 	ft_add_token(data, token);
// 	i++;

// }
