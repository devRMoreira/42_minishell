/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:53:20 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/20 16:41:34 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

//only print the env vars that have an = like bash
int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '='))
			ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
