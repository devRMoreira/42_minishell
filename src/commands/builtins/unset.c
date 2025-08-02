/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:53:18 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:45 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	unset_error(char **argv, t_data *data, int i)
{
	char	*tmp;

	tmp = ft_strjoin_3("unset: '", argv[i], "' not a valid identifier");
	ft_print_error(data, tmp, 1);
	free(tmp);
	return (1);
}

static int	valid_var(char *str)
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

static int	find_var(t_data *data, char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, key_len) == 0
			&& data->envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_var(t_data *data, int index)
{
	char	**new_envp;
	int		i;
	int		j;
	int		size;

	size = 0;
	while (data->envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * size);
	if (!new_envp)
		return ;
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != index)
		{
			new_envp[j] = ft_strdup(data->envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	ft_free_split(data->envp);
	data->envp = new_envp;
}

int	ft_unset(char **argv, t_data *data)
{
	int	i;
	int	res;
	int	var_pos;

	i = 1;
	res = 0;
	while (argv[i])
	{
		if (!valid_var(argv[i]))
			res = unset_error(argv, data, i);
		else
		{
			var_pos = find_var(data, argv[i]);
			if (var_pos >= 0)
				remove_var(data, var_pos);
		}
		i++;
	}
	return (res);
}
