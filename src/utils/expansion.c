/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:27:19 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/08 09:35:54 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_exit_code(t_data *data, char *res, int *i)
{
	char	*temp;
	char	*value;

	temp = ft_itoa(data->exit_code);
	value = ft_strjoin(res, temp);
	free(temp);
	free(res);
	(*i)++;
	return (value);
}

static char	*handle_env_var(t_data *data, char *str, int *i, char *res)
{
	int		start;
	char	*temp;
	char	*value;

	start = *i;
	if (ft_isdigit(str[*i]))
		(*i)++;
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	temp = ft_substr(str, start, *i - start);
	value = ft_get_env(data, temp);
	free(temp);
	if (value)
		temp = value;
	else
		temp = "";
	value = ft_strjoin(res, temp);
	free(res);
	return (value);
}

static char	*handle_literal_dollar(char *res)
{
	char	*value;

	value = ft_strjoin(res, "$");
	free(res);
	return (value);
}

static char	*handle_plain_text(char *str, int *i, char *res)
{
	int		start;
	char	*temp;
	char	*value;

	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	value = ft_strjoin(res, temp);
	free(temp);
	free(res);
	return (value);
}

char	*ft_expand_var(t_data *data, char *str, int *i)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			(*i)++;
			if (str[*i] == '?')
				res = handle_exit_code(data, res, i);
			else if (ft_isalpha(str[*i]) || str[*i] == '_'
				|| ft_isdigit(str[*i]))
				res = handle_env_var(data, str, i, res);
			else
				res = handle_literal_dollar(res);
		}
		else
			res = handle_plain_text(str, i, res);
	}
	return (res);
}
