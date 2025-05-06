/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:00:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 18:13:50 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_envp(char **envp)
{
	int i = -1;
	while(envp && envp[++i])
		free(envp[i]);
	free(envp);
}

static void free_tokens(t_token *tokens)
{
	t_token *temp;

	while(tokens)
	{
		temp = tokens->next;
		free(tokens->input);
		free(tokens);
		tokens = temp;
	}
}

static void free_cmds(t_cmd *cmds)
{
	t_cmd *temp;
	int i;

	while(cmds)
	{
		temp = cmds->next;
		i = -1;
		if(cmds->argv)
		{
			while(cmds->argv[++i])
				free(cmds->argv[i]);
			free(cmds->argv);
		}
		free(cmds->path);
		free(cmds);
		cmds = temp;
	}
}

void ft_free_data(t_data *data)
{
	if(!data)
		return ;
	free(data->input);
	free_envp(data->envp);
	free_tokens(data->tokens);
	free_cmds(data->cmds);
	free(data);
}
