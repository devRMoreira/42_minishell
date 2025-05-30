/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:05:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/30 01:05:29 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//we first need to check if its to be considered a path or just a cmd
//ls or the entire /usr/bin/ls
//all envp paths come seperated by :
//we build the cmd path
//we basically just join the path + / + the cmd  |to create the complete path
static char	*try_paths(char **all_paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char *cmd, t_data *data)
{
	char	*path;
	char	*cmd_path;
	char	**all_paths;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = ft_get_env(data, "PATH");
	if (!path)
		return (NULL);
	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	cmd_path = try_paths(all_paths, cmd);
	ft_free_split(all_paths);
	return (cmd_path);
}

//we check if it exited normally like from finishing its task or the exit above
//if it was killed by a signal
//the bash status codes for these signals are +128 of their value
static void	run_cmd(char *path, char **argv, t_data *data)
{
	execve(path, argv, data->envp);
	ft_print_error(data, strerror(errno), 126);
	exit(data->exit_code);
}

static int	check_path(char **argv, t_data *data, char **path)
{
	char	*error;

	*path = get_cmd_path(argv[0], data);
	if (!*path)
	{
		error = ft_strjoin(argv[0], ": command not found");
		ft_print_error(data, error, 127);
		free(error);
		return (0);
	}
	return (1);
}

static void	execute_command(char **argv, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (ft_is_builtin(argv[0]))
		data->exit_code = ft_exec_builtin(argv, data);
	else if (check_path(argv, data, &path))
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
void ft_exec_cmds(t_data *data)
{
	t_cmd *cmd = data->cmds;
	int backup_stdin = dup(STDIN_FILENO);
	int backup_stdout = dup(STDOUT_FILENO);

	while(cmd)
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			cmd = cmd->next;
			continue;
		}

		//if it has fd's set them accordingly
		if(cmd->input_fd != -1)
			dup2(cmd->input_fd, STDIN_FILENO);
		if(cmd->output_fd != -1)
			dup2(cmd->output_fd, STDOUT_FILENO);


		execute_command(cmd->argv, data);
		dup2(backup_stdin, STDIN_FILENO);
		dup2(backup_stdout, STDOUT_FILENO);
		cmd = cmd->next;
	}

	close(backup_stdin);
	close(backup_stdout);
}
