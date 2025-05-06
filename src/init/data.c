/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:37:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 18:00:39 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char ** get_envp(char **envp)
{
	int total = 0;
	int i = -1;
	char **new;

	while(envp[total])
		total++;

	new = malloc(sizeof(char*) * (total + 1));
	if(!new)
		return NULL;

	while(++i < total)
		new[i] = ft_strdup(envp[i]);

	new[total] = NULL;

	return new;
}

t_data *ft_init_data(char **envp)
{
	t_data *data = malloc(sizeof(data));
	if(!data)
		return (NULL);

	data->input = NULL;
	data->envp = get_envp(envp);
	data->exit_status = 0;
	data->tokens = NULL;
	data->cmds = NULL;

	return data;
}

