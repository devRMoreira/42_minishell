/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:43:58 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/26 13:51:14 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_is_empty(char *s)
{
	int	i;

	i = 0;
	while (ft_is_space(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

t_token_type	ft_get_operator_type(char c, char next)
{
	if (c == '|' && next != '|')
		return (PIPE);
	if (c == '<' && next == '<')
		return (HEREDOC);
	if (c == '<')
		return (REDIRIN);
	if (c == '>' && next == '>')
		return (APPEND);
	if (c == '>')
		return (REDIROUT);
	return (WORD);
}

char	*ft_create_word(char *str1, char *str2)
{
	char	*new;

	new = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (new);
}
