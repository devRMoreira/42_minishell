/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:43:55 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/05 15:56:41 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd)
	{
		cmd->argv = NULL;
		cmd->path = NULL;
		cmd->input_fd = -1;
		cmd->output_fd = -1;
		cmd->pipe[0] = -1;
		cmd->pipe[1] = -1;
		cmd->next = NULL;
	}
	return (cmd);
}

void	ft_clean_cmds(t_data *data)
{
	if (data->cmds)
	{
		ft_free_cmds(data->cmds);
		data->cmds = NULL;
	}
}

void	ft_close_pipes(t_cmd *cmds)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd && cmd->next)
	{
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
		cmd = cmd->next;
	}
}
