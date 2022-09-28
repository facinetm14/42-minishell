/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/09/28 23:43:52 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
#include "../inc/parser.h"

// char	*find_path_in_envp(t_prgm vars)
// {
// 	char	*path_name;
// 	char	*path_env;
// 	char	*test;
// 	int		len_path_env;

// 	path_name = "PATH=";
// 	path_env = NULL;
// 	test = NULL;
// 	len_path_env = 0;
// 	while (*(vars.env))
// 	{
// 		test = ft_strnstr(*(vars.env), path_name, 5);
// 		if (test)
// 		{
// 			path_env = *(vars.env);
// 			len_path_env = ft_strlen(path_env);
// 			break ;
// 		}
// 		else
// 			(*(vars.env))++;
// 	}
// 	path_env = ft_substr(path_env, 5, len_path_env);
// 	return (path_env);
// }

void	init_each_token(t_token *token)
{
	token->in = NULL;
	token->out = NULL;
	token->infile = NULL;
	token->outfile = NULL;
	token->bin = NULL;
	token->built_in = 0;
	token->options = NULL;
	token->t_str_exp = NULL;
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
	vars->env_head = NULL;
	vars->env_head = init_env(vars);
}
