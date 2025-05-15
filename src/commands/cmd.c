/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:05:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/15 16:34:56 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_cmd_path(char *cmd, t_data *data)
{
	//we first need to check if it has the full path or its just the cmd itself
	//like just ls or the entire /usr/bin/ls
	if(ft_strchr(cmd, '/'))
	{
		if(access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}

	char *path = ft_get_env_var(data, "PATH");
	if(!path)
		return NULL;

	//all envp paths come seperated by :
	char **all_paths = ft_split(path, ':');
	if(!all_paths)
		return NULL;

	//we build the cmd
	char *cmd_path = NULL;
	int i = -1;

	while(all_paths[++i])
	{
		//holding it in a temp var to not make messy lines with 2 strjoins
		//we basically just join the path + a / to create the path then the cmd
		char *temp = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);

		//if good return it for execution
		if(access(cmd_path, X_OK) == 0)
		{
			ft_free_split(all_paths);
			return cmd_path;
		}
		free(cmd_path);
	}

	ft_free_split(all_paths);
	return NULL;
}

void ft_execute_command(char **argv, t_data *data)
{
	pid_t pid;
	int status;
	char *path;
	char *err;

	//TODO builtins next
	if(ft_is_builtin(argv[0]))
	{
		data->exit_status = ft_exec_builtin(argv, data);
	}
	else
	{
		path = get_cmd_path(argv[0], data);
		if(!path)
		{
			err = ft_strjoin(argv[0], ": command not found");
			ft_print_error(data, err, 127);
			free(err);
			return ;
		}

		pid = fork();
		if (pid == -1)
		{
			free(path);
			ft_print_error(data, "fork failed", 1);
			return ;
		}

		if (pid == 0)
		{
			execve(path, argv, data->envp);
			ft_print_error(data, strerror(errno), 126);
			exit(data->exit_status);
		}

		free(path);
		waitpid(pid, &status, 0);
		//we check if it exited normally like from finishing its task or the exit above
		if(WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		//if it was killed by a signal
		else if (WIFSIGNALED(status))
			//the bash status codes for these signals are +128 of their value
			data->exit_status = 128 + WTERMSIG(status);
	}

}
