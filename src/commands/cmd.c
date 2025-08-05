/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:05:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/08/05 15:59:25 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fd_reset(t_cmd *cmd, int backup_stdin, int backup_stdout)
{
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
}

static void	run_cmd(char *path, char **argv, t_data *data)
{
	execve(path, argv, data->envp);
	ft_print_error(data, strerror(errno), 126);
	exit(data->exit_code);
}

static void	execute_command(char **argv, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (ft_is_builtin(argv[0]))
		data->exit_code = ft_exec_builtin(argv, data);
	else if (ft_check_path(argv, data, &path))
	{
		pid = fork();
		if (pid == -1)
		{
			free(path);
			ft_print_error(data, "fork failed", 1);
			return ;
		}
		if (pid == 0)
			run_cmd(path, argv, data);
		free(path);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
	}
}

static void	exec_single_cmd(t_data *data, int backup_stdin, int backup_stdout)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	while (cmd)
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->input_fd != -1)
			dup2(cmd->input_fd, STDIN_FILENO);
		if (cmd->output_fd != -1)
			dup2(cmd->output_fd, STDOUT_FILENO);
		execute_command(cmd->argv, data);
		fd_reset(cmd, backup_stdin, backup_stdout);
		cmd = cmd->next;
	}
}

void	ft_exec_cmds(t_data *data)
{
	int		backup_stdin;
	int		backup_stdout;

	if (ft_has_pipes(data->cmds))
	{
		ft_exec_pipes(data);
		return ;
	}
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	exec_single_cmd(data, backup_stdin, backup_stdout);
	close(backup_stdin);
	close(backup_stdout);
}
