/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:08:04 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/08 09:36:18 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_single_quotes(char *str, int *i, char *res)
{
	int		start;
	char	*temp;
	char	*segment;

	temp = ft_strjoin(res, "'");
	free(res);
	res = temp;
	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	if (!temp)
		return (free(res), NULL);
	segment = ft_strjoin(res, temp);
	free(res);
	free(temp);
	res = segment;
	if (str[*i] == '\'')
	{
		temp = ft_strjoin(res, "'");
		free(res);
		res = temp;
		(*i)++;
	}
	return (res);
}

static char	*process_inside_double_quotes(t_data *data, char *str, int *i)
{
	char	*segment;
	char	*temp;
	char	*expand;

	segment = ft_strdup("");
	if (!segment)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '\'')
		{
			temp = ft_strjoin(segment, "'");
			free(segment);
			segment = temp;
			(*i)++;
			continue ;
		}
		expand = ft_expand_var(data, str, i);
		temp = ft_strjoin(segment, expand);
		free(segment);
		free(expand);
		segment = temp;
	}
	return (segment);
}

static char	*handle_double_quotes(t_data *data, char *str, int *i, char *res)
{
	char	*temp;
	char	*segment;

	temp = ft_strjoin(res, "\"");
	free(res);
	res = temp;
	(*i)++;
	segment = process_inside_double_quotes(data, str, i);
	if (!segment)
		return (free(res), NULL);
	temp = ft_strjoin(res, segment);
	free(res);
	free(segment);
	res = temp;
	if (str[*i] == '"')
	{
		temp = ft_strjoin(res, "\"");
		free(res);
		res = temp;
		(*i)++;
	}
	return (res);
}

static char	*handle_dollar_or_text(t_data *data, char *str, int *i, char *res)
{
	int		start;
	char	*temp;
	char	*segment;
	char	*expand;
	int		j;

	if (str[*i] == '$')
	{
		j = *i - 1;
		while (j >= 0 && (str[j] == ' ' || str[j] == '\t'))
			j--;
		if (j >= 1 && str[j - 1] == '<' && str[j] == '<')
		{
			start = *i;
			while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
				&& str[*i] != '\n' && str[*i] != '\'' && str[*i] != '"')
				(*i)++;
			temp = ft_substr(str, start, *i - start);
			if (!temp)
				return (free(res), NULL);
			segment = ft_strjoin(res, temp);
			free(temp);
			free(res);
			return (segment);
		}
		if (str[*i + 1] == '\'')
		{
			(*i) += 2;
			start = *i;
			while (str[*i] && str[*i] != '\'')
				(*i)++;
			temp = ft_substr(str, start, *i - start);
			if (!temp)
				return (free(res), NULL);
			segment = ft_strjoin(res, temp);
			free(temp);
			free(res);
			if (str[*i] == '\'')
				(*i)++;
			return (segment);
		}
		expand = ft_expand_var(data, str, i);
		segment = ft_strjoin(res, expand);
		free(res);
		free(expand);
		return (segment);
	}
	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	temp = ft_substr(str, start, *i - start);
	if (!temp)
		return (free(res), NULL);
	segment = ft_strjoin(res, temp);
	free(temp);
	free(res);
	return (segment);
}

char	*ft_expand(t_data *data, char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			res = handle_single_quotes(str, &i, res);
		else if (str[i] == '"')
			res = handle_double_quotes(data, str, &i, res);
		else
			res = handle_dollar_or_text(data, str, &i, res);
	}
	return (res);
}
