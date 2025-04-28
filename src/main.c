/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/04/28 12:00:52 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>




int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	t_data data;

	while(1)
	{
		//* get input
		data.input = readline("cenas > ");
		printf("%s\n", data.input);
		add_history(data.input);
		if(!ft_strncmp(data.input, "pwd", 3))
		{
		HIST_ENTRY **history = history_list();
        if (history)
        {
            for (int i = 0; history[i]; i++)
            {
                printf("%d: %s\n", i + history_base, history[i]->line);
            }
        }
		}

		// free(data.input);


		// //* dir
		// data.pwd = getcwd(NULL, 0);
		// printf("%s\n", data.pwd);

		// //* change dir
		// chdir("../..");
		// printf("chdir->../..\n");
		// data.pwd = getcwd(NULL, 0);
		// printf("%s\n", data.pwd);

	}
}


