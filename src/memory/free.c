/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:00:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/28 11:22:41 by rimagalh         ###   ########.fr       */
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
	free(data);
}
