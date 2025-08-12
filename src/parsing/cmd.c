/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:50:58 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/12 19:49:37 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	parse_redirects(t_data *data, t_cmd *cmd, t_token **temp)
{
	char	*file;
	t_redir	*new_redir;

	if (*temp && (*temp)->type == PIPE
		&& (*temp)->next && (*temp)->next->type == PIPE)
		return (ft_syntax_error(data, (*temp)->next),
			ft_clean_cmds(data), 0);
	while (*temp && ((*temp)->type == REDIRIN || (*temp)->type == REDIROUT
		|| (*temp)->type == HEREDOC || (*temp)->type == APPEND))
	{
		if (!(*temp)->next || (*temp)->next->type != WORD)
			return (ft_syntax_error(data, (*temp)->next),
				ft_clean_cmds(data), 0);
		file = (*temp)->next->input;
		if (!file || !*file)
			return (ft_print_error(data, "ambiguous redirect", 1),
				ft_clean_cmds(data), 0);
		new_redir = ft_new_redir((*temp)->type, file);
		if (!new_redir)
			return (ft_clean_cmds(data), 0);
		ft_add_redir_to_cmd(cmd, new_redir);
		*temp = (*temp)->next->next;
	}
	return (1);
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
		new = ft_new_cmd();
		if (!new)
			return (ft_clean_cmds(data), 0);
		if (!data->cmds)
			data->cmds = new;
		else
			last->next = new;
		last = new;
		if (!parse_redirects(data, new, &temp))
			return (0);
		new->argv = ft_build_argv(temp);
		if (!new->argv)
			return (ft_clean_cmds(data), 0);
		while (temp && temp->type == WORD)
			temp = temp->next;
		if (!parse_redirects(data, new, &temp))
			return (0);
		if (temp && temp->type == PIPE)
		{
			temp = temp->next;
			// due to the way expansion and parsing was done
			// on commands like ls | $random_var, when a var after a pipe expands to nothing
			// it still needs an empty command afterwards to preserve pipe structure
			// and not output on the terminal
			// doing it in a better way would mean remaking the flow of expansion/parsing
			if (!temp)
			{
				new = ft_new_cmd();
				if (!new)
					return (ft_clean_cmds(data), 0);
				if (!data->cmds)
					data->cmds = new;
				else
					last->next = new;
				last = new;

				new->argv = malloc(sizeof(char *) * 1);
				if (!new->argv)
					return (ft_clean_cmds(data), 0);
				new->argv[0] = NULL;
			}
		}
	}
	return (1);
}
