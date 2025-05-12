/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:07:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/12 17:44:48 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_free_argv(char **argv)
{
	int i = -1;
	while(argv[++i])
		free(argv[i]);
	free(argv);
}

char **ft_build_argv(t_token *tokens)
{
		int argc = 0;
		t_token *temp = tokens;

		while(temp)
		{
			argc++;
			temp = temp->next;
		}

		char **argv = malloc(sizeof(char *) * (argc + 1));
		if(!argv)
			return NULL;

		temp = tokens;
		int i = 0;
		while(temp)
		{
			argv[i] = ft_strdup(temp->input);
			if(!argv[i])
				return ft_free_argv(argv), NULL;

			temp = temp->next;
			i++;
		}
	argv[i] = NULL;
	return argv;
}
