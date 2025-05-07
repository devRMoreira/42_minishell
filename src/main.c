/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/07 15:54:29 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

const char *debugTokenToString(t_token_type type)
{
    switch (type)
    {
        case WORD:
            return "WORD";
        case PIPE:
            return "PIPE";
        case REDIRIN:
            return "REDIRIN";
        case REDIROUT:
            return "REDIROUT";
        case HEREDOC:
            return "HEREDOC";
        case APPEND:
            return "APPEND";
        default:
            return "UNKNOWN";
    }
}

void debugPrintTokens(t_data *data)
{
    t_token *temp = data->tokens;
    while (temp)
    {
        ft_printf("Token: \"%s\", Type: %s\n", temp->input, debugTokenToString(temp->type));
        temp = temp->next;
    }
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data *data = ft_init_data(envp);
	int status;

	while(1)
	{
		//* get input
		data->input = readline("cenas > ");

		if(data->input)
		{
			//always free tokens
			free_tokens(data->tokens);
			data->tokens = NULL;

			//*add to RL history if ok
			if(!ft_parsing(data->input, data))
				add_history(data->input);

			debugPrintTokens(data);

			//* free after it's used
			free(data->input);
		}
		else
		{
			//TODO !input, signals, eof
		}

	}

	status = data->exit_status;
	rl_clear_history();
	ft_free_data(data);
	return status;
}


