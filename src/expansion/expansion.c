/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:08:04 by rimagalh          #+#    #+#             */
/*   Updated: 2025/06/16 16:02:51 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(t_data *data, char *str, int *i)
{
	char *value;
	char *res;
	char *temp;
	int start;

	res = ft_strdup("");
	if (!res)
		return (NULL);

	while(str[*i] && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			(*i)++;
			//exit code
			if(str[*i] == '?')
			{
				temp = ft_itoa(data->exit_code);
				value = ft_strjoin(res, temp);
				free(temp);
				free(res);
				res = value;
				(*i)++;
			}
			//check if its a var, must start with _ OR letter
			else if(ft_isalpha(str[*i]) || str[*i] == '_')
			{
				start = *i;
				while(str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
					(*i)++;
				temp = ft_substr(str, start, *i - start);
				value = ft_get_env(data, temp);
				free(temp);
				if (value)
					temp = value;
				else
					temp = "";
				value = ft_strjoin(res, temp);
				free(res);
				res = value;
			}
			//literal $
			else
			{
				value = ft_strjoin(res, "$");
				free(res);
				res = value;
			}
		}
		else
		//plain text
		{
			start = *i;
			while(str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '"')
				(*i)++;
			temp = ft_substr(str, start, *i - start);
			value = ft_strjoin(res, temp);
			free(temp);
			free(res);
			res = value;
		}
	}
	return (res);
}

char	*ft_expand(t_data *data, char *str)
{
	int i;
	int start;
	char *res;
	char *temp;
	char *segment;
	char *expand;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);

	while(str[i])
	{
		//single quotes is literal
		//so we copy everything until next single
		if(str[i] == '\'')
		{
			temp = ft_strjoin(res, "'");
			free(res);
			res = temp;

			start = ++i;
			while (str[i] && str[i] != '\'')
				i++;
			temp = ft_substr(str, start, i - start);
			if (!temp)
				return (free(res), NULL);
			segment = ft_strjoin(res, temp);
			free(res);
			free(temp);
			res = segment;
			if (str[i] == '\'')
			{
				temp = ft_strjoin(res, "'");
				free(res);
				res = temp;
				i++;
			}
		}
		//double quotes
		//we call helper to expand //* inside
		else if (str[i] == '"')
		{
			temp = ft_strjoin(res, "\"");
			free(res);
			res = temp;

			i++;
			segment = ft_strdup("");
			if(!segment)
				return (free(res), NULL);
			while(str[i] && str[i] != '"')
			{
				if(str[i] == '\'')
				{
					temp = ft_strjoin(segment, "'");
					free(segment);
					segment = temp;
					i++;
					continue;
				}
				expand = expand_var(data, str, &i);
				temp = ft_strjoin(segment, expand);
				free(segment);
				free(expand);
				segment = temp;
			}
			temp = ft_strjoin(res, segment);
			free(res);
			free(segment);
			res = temp;

			if (str[i] == '"')
			{
				temp = ft_strjoin(res, "\"");
				free(res);
				res = temp;
				i++;
			}
		}
		else
		{
			//its just a var so call helper otherwise its plain text
			if (str[i] == '$')
			{
				expand = expand_var(data, str, &i);
				segment = ft_strjoin(res, expand);
				free(res);
				free(expand);
				res = segment;
			}
			else
			{
				start = i;
				while(str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '"')
					i++;
				temp = ft_substr(str, start, i - start);
				if(!temp)
					return (free(res), NULL);
				segment = ft_strjoin(res, temp);
				free(temp);
				free(res);
				res = segment;
			}
		}
	}
	return (res);
}
