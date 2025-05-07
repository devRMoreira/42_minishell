/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/07 15:16:25 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void debugPrintTokens(t_data *data)
{
	t_token *temp = data->tokens;
	while (temp)
	{
    	printf("Token: \"%s\", Type: %d\n", temp->input, temp->type);
    	temp = temp->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data *data = ft_init_data(envp);

	while(1)
	{
		//* get input
		data->input = readline("cenas > ");

		if(data->input)
		{
			//*add to RL history if ok
			if(!ft_parsing(data->input, data))
				add_history(data->input);
			debugPrintTokens(data);

			//* free after it's used
			free(data->input);
		}
		else
		{
			//TODO !input
		}

	}

	ft_free_data(data);
	return 0;
}


