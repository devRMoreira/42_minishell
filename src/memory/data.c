/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:37:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/20 17:35:48 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_envp(char **envp)
{
	int		total;
	int		i;
	char	**new;

	total = 0;
	i = -1;
	while (envp[total])
		total++;
	new = malloc(sizeof(char *) * (total + 1));
	if (!new)
		return (NULL);
	while (++i < total)
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			while (--i >= 0)
				free(new[i]);
			free(new);
			return (NULL);
		}
	}
	new[total] = (NULL);
	return (new);
}

//added get pwd to avoid any non existing pwd nonsense
t_data	*ft_init_data(char **envp)
{
	t_data	*data;
	char	*pwd;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->input = NULL;
	data->envp = get_envp(envp);
	if (!data->envp)
		return (free(data), NULL);
	if (!ft_get_env(data, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			ft_set_env(data, "PWD", pwd);
			free(pwd);
		}
	}
	data->exit_code = 0;
	data->tokens = NULL;
	data->cmds = NULL;
	return (data);
}
