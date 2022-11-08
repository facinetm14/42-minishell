/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:53:59 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/18 15:53:59 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	erase_prompt(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	new_prompt(int sign_num)
{
	ft_putstr_fd("\b\b", 1);
	if (SIGINT == sign_num)
		erase_prompt();
}

void	exit_shell(int sign_num)
{
	if (SIGQUIT == sign_num)
	{
		kill(0, SIGKILL);
		exit(0);
	}
}
