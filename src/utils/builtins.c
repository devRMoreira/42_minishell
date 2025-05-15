/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:13:03 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/15 16:49:44 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_is_builtin(char *cmd)
{
    if (!cmd)
        return 0;

    if(ft_strcmp(cmd, "echo") == 0)
		return 1;

	return 0;
}

int ft_exec_builtin(char **argv, t_data *data)
{
    if (!argv || !argv[0])
        return 1;

    if (ft_strcmp(argv[0], "echo") == 0)
        return ft_echo(argv);

    return 1;
}
