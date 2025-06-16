/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:45:46 by rimagalh          #+#    #+#             */
/*   Updated: 2025/06/16 15:03:52 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_quotes(char *input, int *i)
{
	char	quote;
	char	*end_quote;
	char	*part;

	quote = input[*i];
	(*i)++;
	end_quote = ft_strchr(&input[*i], quote);
	if (!end_quote)
		return (NULL);
	part = ft_substr(input, *i, end_quote - &input[*i]);
	if (!part)
		return (NULL);
	*i += (end_quote - &input[*i]) + 1;
	// printf("After quotes: i=%d, char='%c'\n", *i, input[*i]);
	return (part);
}

static int	parse_operator(char *input, int *i, t_data *data)
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

static char	*collect_word(char *input, int *i)
{
	char	*word;
	char	*part;
	char	*temp;

	word = ft_strdup("");
	while (input[*i] && ((!ft_is_space(input[*i]) && !ft_is_operator(input[*i])) || input[*i] == '\'' || input[*i] == '"'))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			part = handle_quotes(input, i);
		else
			part = ft_substr(input, (*i)++, 1);
		if (!part)
			return (free(word), NULL);
		//printf("After handle_quotes: i=%d, char='%c'\n", *i, input[*i]);

		temp = ft_create_word(word, part);
		word = temp;
	}
	return (word);
}

static int	parse_word(char *input, int *i, t_data *data)
{
	char	*word;
	t_token	*token;

	word = collect_word(input, i);
	if (!word)
		return (0);
	token = ft_new_token(word, ft_strlen(word), WORD);
	free(word);
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
			if (!parse_operator(input, &i, data))
				return (0);
		}
		else if (!parse_word(input, &i, data))
			return (0);
	}
	return (1);
}
