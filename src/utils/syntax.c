/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:37:57 by rimagalh          #+#    #+#             */
/*   Updated: 2025/07/15 14:45:10 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_pipe_end(t_data *data, char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && ft_is_space(input[i]))
		i--;
	if (i >= 0 && input[i] == '|')
		return (ft_print_error(data,
				"syntax error near unexpected token `|'", 2), 0);
	return (1);
}
