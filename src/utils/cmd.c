/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:07:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/30 00:52:38 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	total_tokens(t_token *tokens)
{
	int	res;

	res = 0;
	while (tokens && tokens->type == WORD)
	{
		res++;
		tokens = tokens->next;
	}
	return (res);
}

char	**ft_build_argv(t_token *tokens)
{
	int		i;
	int		argc;
	char	**argv;
	t_token	*temp;

	argc = total_tokens(tokens);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	temp = tokens;
	i = 0;
	while (temp && temp->type == WORD)
	{
		argv[i] = ft_strdup(temp->input);
		if (!argv[i])
			return (ft_free_split(argv), NULL);
		temp = temp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
