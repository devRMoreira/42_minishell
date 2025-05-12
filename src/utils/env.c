/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:52:25 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/12 17:57:32 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_get_env_var(t_data *data, const char *val)
{
	int i = 0;
	int val_size = ft_strlen(val);

	while(data->envp[i])
	{
		if(!ft_strncmp(data->envp[i], val, val_size) &&
			data->envp[i][val_size] == '=')
		{
			return data->envp[i] + val_size + 1;
		}
		i++;
	}

	return NULL;
}

//* !ft_strncmp matches the value we want to find cuz returns 0 on equal comparison
//* and if the next character is = cuz of PATH= on envp strings
//* and to return it skips the whole PATH= and sends the cut string directly
//* by sending the pointer to the char next to the =
//* "PATH=/usr/bin:/bin" -> returns the "/usr/bin:/bin"
//* otherwise returns NULL by default which means it didn't find it
