/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 18:30:38 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data *data = ft_init_data(envp);

	while(1)
	{
		//* get input
		data->input = readline("cenas > "); //! free after being used

		if(data -> input)
		{
			//*add to RL history if ok
			if(!ft_parsing(data->input, &data))
				add_history(data->input);


			free(data->input);
		}
		else
		{

		}

		ft_free_data(data);
	}

	return 0;
}


