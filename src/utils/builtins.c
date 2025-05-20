/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:13:03 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/20 18:11:00 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	ft_exec_builtin(char **argv, t_data *data)
{
	if (!argv || !argv[0])
		return (1);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(argv, data));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv, data));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(data));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, data));
	return (1);
}
