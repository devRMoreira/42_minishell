/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:57:51 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/12 19:45:43 by rimagalh         ###   ########.fr       */
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

static void	exec_pipe_cmd(t_cmd *cmd, t_data *data, t_cmd *prev_cmd)
{
	pid_t	pid;
	char buffer[4096];

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
		if (!ft_setup_redirections(cmd, data))
		{
			ft_close_pipes(data->cmds);
			exit(1);
		}
		ft_close_pipes(data->cmds);
		// If command is empty, consume input to prevent SIGPIPE to previous command
		// otherwise exit codes will be all wrong because it gives the exit code for the
		// first command erroring since the pipe didn't work
		if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		{
			while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0)
				;
			exit(0);
		}
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

	cmd = data->cmds;
	cmd_count = count_commands(cmd);
	if (cmd_count < 2)
		return ;
	setup_pipes(data->cmds, data);
	prev_cmd = NULL;
	while (cmd)
	{
		exec_pipe_cmd(cmd, data, prev_cmd);
		prev_cmd = cmd;
		cmd = cmd->next;
	}
	ft_close_pipes(data->cmds);
	ft_wait_pipes(data, cmd_count);
}
