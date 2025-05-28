/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:16:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/28 16:00:38 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static int	total_tokens(t_token *tokens)
{
	int	res;

	res = 0;
	while (tokens->type == WORD)
	{
		res++;
		tokens = tokens->next;
	}
	return (res);
}

static int handle_redir(t_token_type type, char *input)
{

}

int ft_parse_cmds(t_data *data)
{
	int		fd;
	char	*file;
	t_cmd	*cmd;
	t_cmd	*curr_cmd;
	t_token	*temp = data->tokens;

	curr_cmd = NULL;
	data->cmds = NULL;
	while(temp)
	{
		cmd = ft_new_cmd();
		if(!data->cmds)
			data->cmds = cmd;
		else
			curr_cmd->next = cmd;
		curr_cmd = cmd;

		cmd->argv = ft_build_argv(temp);
		while(temp->type == WORD)
			temp = temp->next;

		while(temp && temp->type != PIPE)
		{

			file = temp->next->input;
			fd = handle_redir(temp->type, file);
			if(temp->type == REDIRIN || temp->type == HEREDOC)
				curr_cmd->input_fd = fd;
			else
				curr_cmd->output_fd = fd;
			temp = temp->next->next;
		}

		if(temp && temp->type == PIPE)
		 	temp = temp->next;
	}
	return (1);
}
