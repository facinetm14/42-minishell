/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 16:12:52 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_each_token(t_token *token)
{
	token->in = NULL;
	token->out = NULL;
	token->infile = NULL;
	token->outfile = NULL;
	token->bin = NULL;
	token->built_in = 0;
	token->options = NULL;
	token->cmd = NULL;
}

void	init_all_tokens(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		init_each_token(&vars->tokens[i]);
		i++;
	}
}

void	init(t_prgm *vars)
{
	vars->pipe_ct = 0;
	vars->p.child = 0;
	vars->env_head = NULL;
	vars->env_head = init_env(vars);
	vars->builts[0] = "cd";
	vars->builts[1] = "echo";
	vars->builts[2] = "env";
	vars->builts[3] = "exit";
	vars->builts[4] = "export";
	vars->builts[5] = "pwd";
	vars->builts[6] = "unset";
	vars->tok_error = 0;
}
