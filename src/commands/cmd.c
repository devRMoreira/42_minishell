/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:05:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/07/30 06:01:39 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//we check if it exited normally like from finishing its task or the exit above
//if it was killed by a signal
//the bash status codes for these signals are +128 of their value
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

//! no pipe yet
void	ft_exec_cmds(t_data *data)
{
	t_cmd	*cmd;
	int		backup_stdin;
	int		backup_stdout;

	cmd = data->cmds;
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
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
		dup2(backup_stdin, STDIN_FILENO);
		dup2(backup_stdout, STDOUT_FILENO);
		cmd = cmd->next;
	}
	close(backup_stdin);
	close(backup_stdout);
}
