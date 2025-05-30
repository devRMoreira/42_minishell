/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:10:41 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/30 02:30:56 by rimagalh         ###   ########.fr       */
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

int	ft_check_path(char **argv, t_data *data, char **path)
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
