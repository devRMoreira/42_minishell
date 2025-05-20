/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:58:47 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/20 16:43:04 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

//exit only takes numbers as args and always writes exit to bash
//it uses the arg to change the exit code otherwise just the one already defined
//helpful to test -> echo "exit 42" | ./minishell ; echo $?

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **argv, t_data *data)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
	{
		ft_free_data(data);
		exit(data->exit_status);
	}
	if (!is_number(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_free_data(data);
		exit(255);
	}
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		data->exit_status = 1;
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	ft_free_data(data);
	exit(exit_code);
}
