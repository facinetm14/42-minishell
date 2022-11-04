/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 01:54:56 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/18 01:54:56 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
* Executing the first command :
* check in : "", "<<", "<"
* check infile
* redirect | stop
* check out "", ">>", "<"
* check outfile
* redirect | stop
* let execute
*/
void	ft_exec_cmd_1(t_prgm *vars, int *let_error)
{
	int	i;

	i = 0;
	
	if (vars->tokens[0].in == NULL)
		;
	while(i < vars->tokens[0].nb_input)
	{
		if (vars->tokens[0].in[i] == IN_REDIRECT)
			ft_infile_checking(vars, let_error);
		if (vars->tokens[0].in[i] == IN_HEREDOC
			|| vars->tokens[0].in[i] == IN_REDIRECT)
		{
			dup2(vars->tokens[0].fd_args[0], 0);
			close(vars->tokens[0].fd_args[0]);
		}
		i++;
	}
	ft_print_err_message(vars);
	if (*let_error != 1)
		ft_bzero(vars->p.error[vars->p.child], 100);
	if (vars->tokens[0].out == NULL && (vars->pipe_ct >= 1))
		dup2(vars->p.fd[0][1], 1);
	i = 0;
	while (i < vars->tokens[0].nb_output)
	{
		if (vars->tokens[0].out[i] == OUT_APPEND)
			vars->tokens[0].fd_args[1] = open(
					vars->tokens[0].outfile[i], O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (vars->tokens[0].out[i] == OUT_REDIRECT)
			vars->tokens[0].fd_args[1] = open(
					vars->tokens[0].outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (vars->tokens[0].out[i] == OUT_APPEND
			|| vars->tokens[0].out[i] == OUT_REDIRECT)
		{
			dup2(vars->tokens[0].fd_args[1], 1);
			if (vars->pipe_ct > vars->p.child
				&& vars->tokens[vars->p.child + 1].in[i] == IN_HEREDOC)
				dup2(vars->p.fd[0][1], 1);
		}
		i++;
	}
}

void	ft_exec_cmd_last(t_prgm *vars, int *let_error)
{
	int	i;

	i = 0;
	if (vars->tokens[vars->pipe_ct].in == NULL)
		dup2(vars->p.fd[vars->pipe_ct - 1][0], 0);
	while (i < vars->tokens[vars->pipe_ct].nb_input)
	{
		if (vars->tokens[vars->p.child].in[i] == IN_HEREDOC)
			;
		else if (vars->tokens[vars->pipe_ct].in[i] == IN_REDIRECT)
			ft_infile_checking(vars, let_error);
		if (vars->tokens[vars->pipe_ct].in[i] == IN_HEREDOC
			|| vars->tokens[vars->pipe_ct].in[i] == IN_REDIRECT)
		{
			dup2(vars->tokens[vars->pipe_ct].fd_args[0], 0);
			close(vars->tokens[vars->pipe_ct].fd_args[0]);
		}
		i++;
	}
	ft_print_err_message(vars);
	if (*let_error != 1)
		ft_bzero(vars->p.error[vars->p.child], 100);
	i = 0;
	while (i < vars->tokens[vars->pipe_ct].nb_output)
	{
		if (vars->tokens[vars->pipe_ct].out[i] == OUT_APPEND)
			vars->tokens[vars->pipe_ct].fd_args[1] = open(
				vars->tokens[vars->pipe_ct].outfile[i],
				O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (vars->tokens[vars->pipe_ct].out[i] == OUT_REDIRECT)
			vars->tokens[vars->pipe_ct].fd_args[1] = open(
				vars->tokens[vars->pipe_ct].outfile[i],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (vars->tokens[vars->pipe_ct].out[i] == OUT_APPEND
			|| vars->tokens[vars->pipe_ct].out[i] == OUT_REDIRECT)
			dup2(vars->tokens[vars->pipe_ct].fd_args[1], 1);
		i++;
	}
}

void	ft_close_fds(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct)
	{
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		i++;
	}
}
