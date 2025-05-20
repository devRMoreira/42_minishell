/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:46:07 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/20 16:15:03 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


//if cd has no args it goes to home
//if just cd it goes to the previous pwd
//if argument, goes to the pwd
//!specific printing just for cd
//!probably look at this later to redo the main printing function
static int print_cd_error(t_data *data, char *error)
{
	ft_printf("minishell: cd: %s: %s\n", error, strerror(errno));
	data->exit_status = 1;
	return 1;
}
static int update_oldpwd(t_data *data)
{
	char *old_pwd = ft_get_env(data, "PWD");
	char *cwd = getcwd(NULL, 0);

	if(!cwd)
		return ft_print_error(data, "cd: error retrieving current directory", 1);
	if(old_pwd)
		ft_set_env(data, "OLDPWD", old_pwd);
	ft_set_env(data, "PWD", cwd);
	free(cwd);
	return 0;
}
int ft_cd(char **argv, t_data *data)
{
	char *path;

	if(!argv[1])
	{
		path = ft_get_env(data, "HOME");
		if(!path)
			return ft_print_error(data, "cd: HOME not set", 1);
	}
	else if(ft_strcmp(argv[1], "-") == 0)
	{
		path = ft_get_env(data, "OLDPWD");
		if(!path)
			return ft_print_error(data, "cd: OLDPWD not set", 1);
		ft_printf("%s\n", path);
	}
	else
		path = argv[1];

	if(chdir(path) != 0)
		return print_cd_error(data, path);


	return update_oldpwd(data);
}
