/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:05:00 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/11 17:49:08 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redir_type(t_redir *redir, t_data *data)
{
	int		fd;
	char	*error;

	if (redir->type == REDIRIN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIROUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		return (ft_handle_heredoc(redir->filename, data));
	else
		return (-1);
	if (fd < 0)
	{
		error = ft_strjoin_3(redir->filename, ": ", strerror(errno));
		if (error)
		{
			ft_printf("minishell: %s\n", error);
			free(error);
		}
		else
			ft_printf("minishell: %s\n", redir->filename);
		return (-1);
	}
	return (fd);
}

int	ft_setup_redirections(t_cmd *cmd, t_data *data)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirects;
	while (redir)
	{
		fd = handle_redir_type(redir, data);
		if (fd < 0)
			return (0);
		if (redir->type == REDIRIN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (1);
}
