/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:38:34 by rimagalh          #+#    #+#             */
/*   Updated: 2025/05/30 02:40:25 by rimagalh         ###   ########.fr       */
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


//!! CHECK OUTPUT ON LINUX OF CMDS WITH QUOTES MIGHT BE BUGGED WSL

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_data *data = ft_init_data(envp);
	int status;

	while(1)
	{
		//* get input
		data->input = readline("minishell > ");

		if(data->input)
		{

			//TODO offset loop cleanup to another func later
			//always free tokens
			ft_free_tokens(data->tokens);
			data->tokens = NULL;

			//*add to RL history if ok
			if(ft_parsing(data->input, data))
			{
				add_history(data->input);

				if(!ft_parse_cmds(data))
				{
					free(data->input);
					continue;
				}

				if(data->cmds)
				{
					ft_exec_cmds(data);
					ft_free_cmds(data->cmds);
					data->cmds = NULL;
				}
				// old no redir execution just in case
				// char **argv = ft_build_argv(data->tokens);
				// if(argv)
				// {
				// 	ft_execute_command(argv, data);
				// 	ft_free_split(argv);
				// }
			}

			// debugPrintTokens(data);

			//* free after it's used
			free(data->input);
		}
		else
		{
			rl_clear_history();
			ft_free_data(data);
			exit(data->exit_code);
		}

	}

	status = data->exit_code;
	rl_clear_history();
	ft_free_data(data);
	return status;
}


