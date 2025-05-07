/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:43:55 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/07 15:55:47 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *ft_new_cmd(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if(cmd)
	{
		cmd->argv = NULL;
		cmd->path = NULL;
		cmd->input_fd = -1;
		cmd->output_fd = -1;
		cmd->pipe[0] = -1;
		cmd->pipe[1] = -1;
		cmd->next = NULL;
	}
	return cmd;
}
