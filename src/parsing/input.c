/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:45:46 by rimagalh          #+#    #+#             */
/*   Updated: 2025/04/28 13:49:29 by rimagalh         ###   ########.fr       */
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
