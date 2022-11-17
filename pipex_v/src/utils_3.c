/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:47:09 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/31 18:47:09 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../inc/pipex.h"

void	ft_generate_p(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct - 1)
	{
		if (pipe(vars->p.fd[i]) < 0)
		{
			perror("Error pipe ");
			exit(0);
		}
		i++;
	}
}

void	free_2_pt(char **pt)
{
	int	i;

	i = 0;
	while (pt[i])
	{
		free(pt[i]);
		i++;
	}
	if (pt)
		free(pt);
}

void	ft_exit_code(int ex_code, int mode)
{
	if (mode == 0)
	{
		printf("%d", g_exit_code);
		g_exit_code = 0;
	}
	else
		g_exit_code = ex_code % 256;
}

int	ft_check_ex_opts(t_prgm *vars)
{
	int	i;

	i = 1;
	while (vars->tok[vars->p.child].opts[i])
	{
		if (i > 1)
		{
			printf("too many arguments\n");
			ft_exit_code(1, 1);
			return (1);
		}
		if (ft_assert_numeric(vars, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	is_numeric(char c)
{
	if (!(c >= '0' && c <= '9') && c != '-')
		return (1);
	return (0);
}
