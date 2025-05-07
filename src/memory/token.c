/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:35:40 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/07 15:55:35 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_add_token(t_data *data, t_token *token)
{
	t_token *temp;
	if(!data->tokens)
		data->tokens = token;
	else
	{
		temp = data->tokens;
		while(temp->next)
			temp = temp->next;
		temp->next = token;
	}
}

t_token *ft_new_token(char *str, int length, t_token_type type)
{
	t_token *token = malloc(sizeof(t_token));
	if(!token)
		return NULL;

	token->input = malloc(length + 1);
	if(!token->input)
	{
		free(token);
		return NULL;
	}
	ft_strlcpy(token->input, str, length + 1);
	token->type = type;
	token->next = NULL;

	return token;
}
