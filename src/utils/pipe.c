/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 08:05:44 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/08 08:07:04 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_wait_pipes(t_data *data, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	ft_has_pipes(t_cmd *cmds)
{
	t_cmd	*temp;

	temp = cmds;
	while (temp)
	{
		if (temp->next)
			return (1);
		temp = temp->next;
	}
	return (0);
}
