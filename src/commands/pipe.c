/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:57:51 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/05 15:59:37 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	do_cmd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		exit(127);
	if (ft_is_builtin(cmd->argv[0]))
	{
		data->exit_code = ft_exec_builtin(cmd->argv, data);
		exit(data->exit_code);
	}
	if (!ft_check_path(cmd->argv, data, &path))
		exit(127);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->argv, data->envp);
	ft_print_error(data, "execve failed", 127);
	free(path);
	exit(127);
}

static void	setup_pipes(t_cmd *cmds, t_data *data)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd && cmd->next)
	{
		if (pipe(cmd->pipe) < 0)
		{
			ft_print_error(data, "pipe failed", 1);
			return ;
		}
		cmd = cmd->next;
	}
}

static void	exec_cmd_in_pipe(t_cmd *cmd, t_data *data, t_cmd *prev_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (prev_cmd)
			dup2(prev_cmd->pipe[0], STDIN_FILENO);
		if (cmd->next)
			dup2(cmd->pipe[1], STDOUT_FILENO);
		if (cmd->input_fd != -1)
			dup2(cmd->input_fd, STDIN_FILENO);
		if (cmd->output_fd != -1)
			dup2(cmd->output_fd, STDOUT_FILENO);
		ft_close_pipes(data->cmds);
		do_cmd(cmd, data);
	}
}

static int	count_commands(t_cmd *cmds)
{
	int		count;
	t_cmd	*temp;

	count = 0;
	temp = cmds;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	ft_exec_pipes(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*prev_cmd;
	int		cmd_count;
	int		i;

	cmd = data->cmds;
	cmd_count = count_commands(cmd);
	if (cmd_count < 2)
		return ;
	setup_pipes(data->cmds, data);
	prev_cmd = NULL;
	while (cmd)
	{
		exec_cmd_in_pipe(cmd, data, prev_cmd);
		prev_cmd = cmd;
		cmd = cmd->next;
	}
	ft_close_pipes(data->cmds);
	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}
