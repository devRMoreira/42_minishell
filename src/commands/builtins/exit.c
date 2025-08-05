/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:58:47 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/05 16:17:20 by rimagalh         ###   ########.fr       */
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

static void	handle_err(char *arg, t_data *data)
{
	char	*error_msg;

	error_msg = ft_strjoin_3("exit: ", arg, ": numeric argument required");
	ft_print_error(data, error_msg, 255);
	free(error_msg);
	ft_free_data(data);
	exit(255);
}

int	ft_exit(char **argv, t_data *data)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	exit_code = data->exit_code;
	if (!argv[1])
	{
		ft_free_data(data);
		exit(exit_code);
	}
	if (!is_number(argv[1]))
		handle_err(argv[1], data);
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		data->exit_code = 1;
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	ft_free_data(data);
	exit(exit_code);
}
