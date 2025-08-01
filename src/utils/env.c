/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:52:25 by rimagalh          #+#    #+#             */
/*   Updated: 2025/07/21 14:52:23 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_key(char **envp, char *key, char *val)
{
	int		i;
	char	*new_key;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	new_key = ft_strjoin_3(key, "=", val);
	if (!new_key)
		return (1);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_key;
			return (0);
		}
		i++;
	}
	free(new_key);
	return (1);
}

static int	add_new_key(t_data *data, char *key, char *val)
{
	int		i;
	int		j;
	char	**new;
	char	*new_key;

	i = 0;
	j = -1;
	new_key = ft_strjoin_3(key, "=", val);
	if (!new_key)
		return (1);
	while (data->envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (free(new_key), 1);
	while (++j < i)
		new[j] = data->envp[j];
	new[i] = new_key;
	new[i + 1] = NULL;
	free(data->envp);
	data->envp = new;
	return (0);
}

int	ft_set_env(t_data *data, char *key, char *val)
{
	if (!key || !val)
		return (1);
	if (update_key(data->envp, key, val) == 0)
		return (0);
	return (add_new_key(data, key, val));
}

char	*ft_get_env(t_data *data, char *val)
{
	int	i;
	int	val_size;

	i = 0;
	val_size = ft_strlen(val);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], val, val_size) && \
			data->envp[i][val_size] == '=')
		{
			return (data->envp[i] + val_size + 1);
		}
		i++;
	}
	return (NULL);
}

void	ft_print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
}

//* !ft_strncmp matches the value we want
// to find cuz returns 0 on equal comparison
//* and if the next character is = cuz of PATH= on envp strings
//* and to return it skips the whole PATH= and sends the cut string directly
//* by sending the pointer to the char next to the =
//* "PATH=/usr/bin:/bin" -> returns the "/usr/bin:/bin"
//* otherwise returns NULL by default which means it didn't find it
