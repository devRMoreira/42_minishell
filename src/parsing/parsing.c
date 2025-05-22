/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:45:46 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/22 14:23:48 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//TODO fix these quotes
// minishell > l's'
// minishell: 's: command not found

static int	ft_parse_operator(char *input, int *i, t_data *data)
{
	int				len;
	t_token			*token;
	t_token_type	type;

	type = ft_get_operator_type(input[*i], input[*i + 1]);
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	token = ft_new_token(input + *i, len, type);
	if (!token)
		return (0);
	ft_add_token(data, token);
	*i += len;
	return (1);
}

static int	ft_parse_word(char *input, int *i, t_data *data)
{
	int		start;
	char	quote;
	t_token	*token;

	start = *i;
	while (input[*i] && !ft_is_space(input[*i]) && !ft_is_operator(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[(*i)++];
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (!input[*i])
				return (ft_print_error(data,
						"syntax error: unclosed quote\n", 258));
		}
		(*i)++;
	}
	if(quote)
		token = ft_new_token(input + (start + 1), *i - start - 2, WORD);
	else
		token = ft_new_token(input + start, *i - start, WORD);
	if (!token)
		return (0);
	ft_add_token(data, token);
	return (1);
}

//need to skip spaces and check if it's an op <>|
//and create tokens based on that
//if we find a quote we need to find a matching one
int	ft_parsing(char *input, t_data *data)
{
	int	i;

	i = 0;
	if (ft_is_empty(input))
		return (0);
	while (input[i])
	{
		while (input[i] && ft_is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (ft_is_operator(input[i]))
		{
			if (!ft_parse_operator(input, &i, data))
				return (0);
		}
		else if (!ft_parse_word(input, &i, data))
			return (0);
	}
	return (1);
}

//! old parsing just in case
// int	ft_parsing(char *input, t_data *data)
// {
// 	int		i;
// 	int		start;
// 	char	quote;
// 	t_token	*token;

// 	i = 0;
// 	if(ft_is_empty(input))
// 		return (0);

// 	while(input[i])
// 	{
//
// 		while(input[i] && ft_is_space(input[i]))
// 			i++;

// 		if(!input[i])
// 			break;
//
// 		if (ft_is_operator(input[i]))
// 		{

//
// 			t_token_type type = ft_get_operator_type(input[i], input[i+1]);
// 			int len;
// 			if(type == HEREDOC || type == APPEND)
// 				len = 2;
// 			else
// 				len = 1;

// 			token = ft_new_token(input + i, len, type);
// 			if(!token)
// 				return 0;
// 			ft_add_token(data, token);
// 			i += len;
// 		}
//
// 		else
// 		{
// 			start = i;
//
// 			while (input[i] && !ft_is_space(input[i])
					//  && !ft_is_operator(input[i]))
// 			{
//
// 				if(input[i] == '"' || input[i] == '\'')
// 				{
//
// 					quote = input[i++];
//
// 					while(input[i] && input[i] != quote)
// 						i++;
//
// 					if(!input[i])
// 						return ft_print_error(data,
//										 "syntax error: unclosed quote\n", 258);

// 				}
// 				i++;
// 			}
//
// 			token = ft_new_token(input + start, i - start, WORD);
// 			if(!token)
// 				return 0;
// 			ft_add_token(data, token);
// 		}
// 	}
// 	return 1;
// }
