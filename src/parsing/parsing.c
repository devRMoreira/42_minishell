/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:45:46 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 16:24:47 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_space(char c)
{
	if(c == 32)
		return 1;
	else if (c >= 9 && c <=13)
		return 1;

	return 0;
}

int ft_is_empty(char *str)
{
	int i ;

	if(!str)
		return (0);

	i = -1;
	while(is_space(str[++i]))
	if(str[i] == '\0')
		return 1;
	return 0;
}

int ft_parsing(char *input, t_data data)
{
	int i = -1;
	int sq = 0;
	int dq = 0;

	while(input[++i])
	{


	}

	return 0;

}
