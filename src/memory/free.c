/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:00:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/08 07:04:06 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->input);
		free(tokens);
		tokens = temp;
	}
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	int		i;

	while (cmds)
	{
		temp = cmds->next;
		i = -1;
		if (cmds->argv)
		{
			while (cmds->argv[++i])
				free(cmds->argv[i]);
			free(cmds->argv);
		}
		if (cmds->input_fd != -1 && cmds->input_fd != STDIN_FILENO)
			close(cmds->input_fd);
		if (cmds->output_fd != -1 && cmds->output_fd != STDOUT_FILENO)
			close(cmds->output_fd);
		if (cmds->pipe[0] != -1)
			close(cmds->pipe[0]);
		if (cmds->pipe[1] != -1)
			close(cmds->pipe[1]);
		free(cmds->path);
		free(cmds);
		cmds = temp;
	}
}

void	ft_free_split(char **strs)
{
	int	i;

	i = -1;
	while (strs && strs[++i])
		free(strs[i]);
	free(strs);
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	free(data->input);
	ft_free_split(data->envp);
	ft_free_tokens(data->tokens);
	ft_free_cmds(data->cmds);
	if (data->backup_stdin != -1)
		close(data->backup_stdin);
	if (data->backup_stdout != -1)
		close(data->backup_stdout);
	free(data);
}
