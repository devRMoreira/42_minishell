/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:00:00 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/11 17:08:30 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*ft_new_redir(t_token_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	ft_add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*temp;

	if (!cmd->redirects)
	{
		cmd->redirects = redir;
		return ;
	}
	temp = cmd->redirects;
	while (temp->next)
		temp = temp->next;
	temp->next = redir;
}

void	ft_free_redirs(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs;
		redirs = redirs->next;
		free(temp->filename);
		free(temp);
	}
}
