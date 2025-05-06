/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/06 16:07:58 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	t_data data;

	while(1)
	{
		//* get input
		data.input = readline("cenas > "); //! free after being used

		ft_parsing(data.input, data);

		//*add to RL history
		if(!ft_is_empty(data.input))
			add_history(data.input);

		//* after being used
		// free(data.input);


		// //*print history on input == pwd
		// if(!ft_strncmp(data.input, "pwd", 3))
		// {
		// 	HIST_ENTRY **history = history_list();
    	//     if (history)
		// 	{
		// 		for (int i = 0; history[i]; i++)
		// 		{
		// 			printf("%d: %s\n", i + history_base, history[i]->line);
		// 		}
		// 	}
		// }
		// rl_clear_history();

		//* dir
		// data.pwd = getcwd(NULL, 0);
		// printf("%s\n", data.pwd);

		// //* change dir
		// chdir("../..");
		// printf("chdir->../..\n");
		// data.pwd = getcwd(NULL, 0);
		// printf("%s\n", data.pwd);

	}

	return 0;
}


