/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:50:58 by rimagalh          #+#    #+#             */
/*   Updated: 2025/06/04 18:24:29 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	clean_cmds(t_data *data)
{
	if (data->cmds)
	{
		ft_free_cmds(data->cmds);
		data->cmds = NULL;
	}
}

static int	handle_fd_redir(t_token_type type, char *input, t_data *data)
{
	int		fd;
	char	*error;

	if (type == REDIRIN)
		fd = open(input, O_RDONLY);
	else if (type == REDIROUT)
		fd = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HEREDOC)
		return (ft_print_error(data, "heredoc no", 1), -1);
	else
		return (-1);
	if (fd < 0)
	{
		error = ft_strjoin(input, ": No such file or directory");
		if (error)
		{
			ft_print_error(data, error, 1);
			free(error);
		}
		else
			return (ft_print_error(data, input, 1), -1);
	}
	return (fd);
}

void	assign_fd(t_cmd *cmd, t_token_type type, int fd)
{
	if (type == REDIRIN || type == HEREDOC)
	{
		if (cmd->input_fd != -1)
			close(cmd->input_fd);
		cmd->input_fd = fd;
	}
	else
	{
		if (cmd->output_fd != -1)
			close(cmd->output_fd);
		cmd->output_fd = fd;
	}
}

int	parse_redirects(t_data *data, t_cmd *cmd, t_token **temp)
{
	int		fd;
	char	*file;

	if (*temp && (*temp)->type == PIPE
		&& (*temp)->next && (*temp)->next->type == PIPE)
		return (ft_syntax_error(data, (*temp)->next),
			clean_cmds(data), 0);
	while (*temp && (*temp)->type != PIPE)
	{
		if (!(*temp)->next || (*temp)->next->type != WORD)
			return (ft_syntax_error(data, (*temp)->next),
				clean_cmds(data), 0);
		file = (*temp)->next->input;
		fd = handle_fd_redir((*temp)->type, file, data);
		if (fd < 0)
			return (clean_cmds(data), 0);
		assign_fd(cmd, (*temp)->type, fd);
		*temp = (*temp)->next->next;
	}
	return (1);
}

t_cmd	*setup_cmd(t_data *data, t_cmd **last, t_token **temp)
{
	t_cmd	*cmd;

	cmd = ft_new_cmd();
	if (!cmd)
		return (clean_cmds(data), NULL);
	if (!data->cmds)
		data->cmds = cmd;
	else
		(*last)->next = cmd;
	*last = cmd;
	cmd->argv = ft_build_argv(*temp);
	if (!cmd->argv)
		return (clean_cmds(data), NULL);
	while (*temp && (*temp)->type == WORD)
		*temp = (*temp)->next;
	return (cmd);
}

int	ft_parse_cmds(t_data *data)
{
	t_cmd	*new;
	t_cmd	*last;
	t_token	*temp;

	temp = data->tokens;
	last = NULL;
	data->cmds = NULL;
	if (temp && temp->type == PIPE)
		return (ft_syntax_error(data, temp), 0);
	while (temp)
	{
		new = setup_cmd(data, &last, &temp);
		if (!new)
			return (0);
		if (!parse_redirects(data, new, &temp))
			return (0);
		if (temp && temp->type == PIPE)
			temp = temp->next;
	}
	return (1);
}
