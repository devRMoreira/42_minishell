/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:46:07 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/16 12:16:07 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int ft_cd(char **argv, t_data *data)
{
	int res;

	data->old_path = getcwd(NULL, 0);
	res = chdir(argv[1]);

	return res;
}
