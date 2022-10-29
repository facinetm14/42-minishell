/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 02:14:40 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/29 02:14:40 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_our_env(t_prgm *vars, char *var)
{
	t_env	*envp;

	envp = vars->env_head;
	while (envp)
	{
		if (ft_strcmp(envp->key, var) == 0 && envp->value)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

int	is_our_env_path(t_prgm *vars)
{
	t_env	*envp;

	envp = vars->env_head;
	while (envp)
	{
		if (ft_strncmp(envp->key, "PATH", 4) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

void	ft_cd(t_prgm *vars)
{
	char	*oldpwd;
	t_env	*envp;

	envp = vars->env_head;
	oldpwd = get_our_env(vars, "PWD");
	if (!vars->tokens[vars->p.child].options[1]
		|| *vars->tokens[vars->p.child].options[1] == '~')
		chdir(getenv("HOME"));
	else
	{
		if (chdir(vars->tokens[vars->p.child].options[1]) == -1)
		{
			perror(vars->tokens[vars->p.child].options[1]);
			ft_exit_code(1, 1);
			return ;
		}
		if (vars->pipe_ct > 0)
		{
			chdir(oldpwd);
			return ;
		}
	}
	ft_update_env(envp, oldpwd);
}

void	ft_update_env(t_env *envp, char *oldpwd)
{
	int		flag;
	char	repo[MAX_LEN_DIR];

	flag = 0;
	while (envp)
	{
		if (ft_strncmp(envp->key, "OLDPWD", 6) == 0)
		{
			if (envp->value)
				free(envp->value);
			envp->value = ft_strdup(oldpwd);
			flag += 1;
		}
		else if (ft_strncmp(envp->key, "PWD", 3) == 0)
		{
			ft_bzero(repo, MAX_LEN_DIR);
			if (envp->value)
				free(envp->value);
			envp->value = ft_strdup(getcwd(repo, MAX_LEN_DIR));
			flag += 1;
		}
		if (flag == 2)
			return ;
		envp = envp->next;
	}
}