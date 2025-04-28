/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/04/28 13:31:40 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int ft_is_space(char c)
{
	return (c == 32 || (c >= 9 && c <=13));
}

static int empty(char *str)
{
	int i ;

	if(!str)
		return (0);

	i = -1;
	while(ft_is_space(str[++i]))
	if(str[i] == '\0')
		return 1;

	return 0;
}


int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	t_data data;

	while(1)
	{
		//* get input
		data.input = readline("cenas > ");

		//* prompt again if empty
		while(empty(data.input))
			data.input = readline("cenas > ");

		// printf("%s\n", data.input);

		//*add to RL history
		add_history(data.input);

		//*print history on input == pwd
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

	return 0;
}


