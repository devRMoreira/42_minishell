/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/02 15:42:01 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_exit(t_data *data)
{
	ft_printf("exit\n");
	rl_clear_history();
	ft_free_data(data);
	exit(data->exit_code);
}

static int	handle_input(t_data *data)
{
	char	*expand;

	ft_free_tokens(data->tokens);
	data->tokens = NULL;
	if (!ft_syntax_check(data, data->input))
	{
		free(data->input);
		return (0);
	}
	add_history(data->input);
	expand = ft_expand(data, data->input);
	free(data->input);
	data->input = expand;
	return (1);
}

static void	handle_cmds(t_data *data)
{
	if (ft_parsing(data->input, data))
	{
		if (!ft_parse_cmds(data))
		{
			free(data->input);
			return ;
		}
		if (data->cmds)
		{
			ft_exec_cmds(data);
			ft_free_cmds(data->cmds);
			data->cmds = NULL;
		}
	}
	free(data->input);
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	t_data	*data;

	(void)ac;
	(void)av;
	data = ft_init_data(envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, ft_handle_sigint);
		data->input = readline("minishell > ");
		if (data->input)
		{
			if (handle_input(data))
				handle_cmds(data);
		}
		else
			handle_exit(data);
	}
	status = data->exit_code;
	rl_clear_history();
	ft_free_data(data);
	return (status);
}
