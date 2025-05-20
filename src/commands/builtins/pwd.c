/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:45:19 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/20 16:43:55 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// passing argv cuz idk if flags are needed so ignoring for now
int	ft_pwd(char **argv, t_data *data)
{
	char	*cwd;

	(void) argv;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_print_error(data, "pwd: error retrieving current directory", 1);
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
