/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:56 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 17:33:59 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_print_error(t_data *data, char* error, int exit_code)
{
	ft_printf("minishell: %s");
	data->exit_status = exit_code;
	return (exit_code);
}
