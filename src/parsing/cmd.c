/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:16:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/30 00:56:33 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void clean_cmds(t_data *data)
{
	if(data->cmds)
	{
		ft_free_cmds(data->cmds);
		data->cmds = NULL;
	}
}
static int handle_redir(t_token_type type, char *input, t_data *data)
{
	int fd;

	if (type == REDIRIN)
		fd = open(input, O_RDONLY);
	else if (type == REDIROUT)
		fd = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HEREDOC)
	{
		return ft_print_error(data, "heredoc no", 1), -1;
	}
	else
		return (-1);
	if (fd < 0)
	{
		return ft_print_error(data, input, 1), -1;
	}
	return (fd);
}


int ft_parse_cmds(t_data *data)
{
	int		fd;
	char	*file;
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;
	t_token	*temp;

	temp = data->tokens;
	last_cmd = NULL;
	data->cmds = NULL;

	while(temp)
	{
		//we alloc a new new_cmd
		new_cmd = ft_new_cmd();
		if(!new_cmd)
			return (clean_cmds(data), 0);

		//if its the first loop we need to leave the first link on data
		//and always allocate the  new_cmd to a new one
		if(!data->cmds)
			data->cmds = new_cmd;
		else
			last_cmd->next = new_cmd;

		last_cmd = new_cmd;

		//build the cmds argv
		new_cmd->argv = ft_build_argv(temp);
		if(!new_cmd->argv)
			return clean_cmds(data), 0;
		//gotta skip the same tokens to check if over or special chars
		while(temp && temp->type == WORD)
			temp = temp->next;

		//check for double pipe
		if(temp && temp->type == PIPE && temp->next && temp->next->type == PIPE)
			return (ft_syntax_error(data, temp->next), clean_cmds(data), 0);

		//if it's a redirect
		while(temp && temp->type != PIPE)
		{

			if (temp->next == NULL || temp->next->type != WORD)
				return (ft_syntax_error(data, temp->next), clean_cmds(data), 0);
			file = temp->next->input;
			fd = handle_redir(temp->type, file, data);
			if(fd < 0)
					return (clean_cmds(data), 0);

			//deal with input redirs
			if(temp->type == REDIRIN || temp->type == HEREDOC)
			{
				//leak check if it already has an fd set
				if(last_cmd->input_fd != -1)
					close(last_cmd->input_fd);
				last_cmd->input_fd = fd;
			}
			//deal with output redirs
			else
			{
				if(last_cmd->output_fd != -1)
					close(last_cmd->output_fd);
				last_cmd->output_fd = fd;
			}
			//we skip the redir token and the filename
			temp = temp->next->next;
		}

		if(temp && temp->type == PIPE)
		 	temp = temp->next;
	}
	return (1);
}
