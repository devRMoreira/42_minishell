/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:16:51 by rimagalh          #+#    #+#             */
/*   Updated: 2025/07/21 14:51:53 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	exp_error(char **argv, t_data *data, int i)
{
	char	*tmp;

	tmp = ft_strjoin_3("export: '", argv[i], "' not a valid identifier");
	ft_print_error(data, tmp, 1);
	free(tmp);
	return (1);
}

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	export_set_env(char **argv, int i, t_data *data, char *eq)
{
	char	*key;
	char	*value;

	key = ft_substr(argv[i], 0, eq - argv[i]);
	if (!valid_identifier(key))
	{
		exp_error(argv, data, i);
		free(key);
		return ;
	}
	value = ft_strdup(eq + 1);
	ft_set_env(data, key, value);
	free(key);
	free(value);
}

static void	export_arg(char **argv, int i, t_data *data)
{
	if (!valid_identifier(argv[i]))
		exp_error(argv, data, i);
	else
		ft_set_env(data, argv[i], "");
}

int	ft_export(char **argv, t_data *data)
{
	int		i;
	char	*eq;

	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
			export_set_env(argv, i, data, eq);
		else
			export_arg(argv, i, data);
		i++;
	}
	if (i == 1)
		ft_print_env(data);
	return (0);
}
