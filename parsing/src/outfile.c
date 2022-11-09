/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 22:57:40 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	count_output(t_prgm *vars)
{
	int	j;
	int	nb_output;

	j = 0;
	nb_output = 0;
	while (vars->tokens[vars->i2].t_str[j] != '\0')
	{
		if (vars->tokens[vars->i2].t_str[j] == '>' && \
			(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j) == NULL && \
			is_between_quotes(vars->tokens[vars->i2].t_str, '"', j) == NULL))
			nb_output++;
		if (j > 0)
		{
			if ((vars->tokens[vars->i2].t_str[j - 1] == '>' && vars->tokens[vars->i2].t_str[j] == '>') && \
				(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j - 1) == NULL && \
				is_between_quotes(vars->tokens[vars->i2].t_str, '"', j - 1) == NULL) && \
				(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j) == NULL && \
				is_between_quotes(vars->tokens[vars->i2].t_str, '"', j) == NULL))
				nb_output--;
		}
		j++;
	}
	return (nb_output);
}

void	subs_outfile(t_prgm *vars, int *start, int index)
{
	int	len_outfile;
	int	j;

	len_outfile = 0;
	j = *start;
	skip_white_spaces(vars, start, vars->i2);
	while (vars->tokens[vars->i2].t_str[j] != '\0' && (vars->tokens[vars->i2].t_str[j] != ' ' && vars->tokens[vars->i2].t_str[j] != '\t'))
	{
		if ((vars->tokens[vars->i2].t_str[j] == '<' || vars->tokens[vars->i2].t_str[j] == '>')
			&& (is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j) == NULL
			&& is_between_quotes(vars->tokens[vars->i2].t_str, '"', j) == NULL))
		{
			vars->tok_error = 1;
			return ;
		}
		len_outfile++;
		j++;
	}
	vars->tokens[vars->i2].outfile[index] = trim_quotes(ft_substr(vars->tokens[vars->i2].t_str, *start, len_outfile++));
	*start += len_outfile - 1;
}

void	extract_outfiles(t_prgm *vars)
{
	int	start;
	int	j;
	int	index;
	int	k;

	j = 0;
	index = 0;
	k = 0;
	vars->tokens[vars->i2].nb_output = count_output(vars);
	if (vars->tokens[vars->i2].nb_output > 0)
	{
		vars->tokens[vars->i2].out = malloc(sizeof(int) * (vars->tokens[vars->i2].nb_output + 1));
		vars->tokens[vars->i2].outfile = malloc(sizeof(char *) * (vars->tokens[vars->i2].nb_output + 1));
		vars->tokens[vars->i2].outfile[vars->tokens[vars->i2].nb_output] = NULL;
	}
	while (vars->tokens[vars->i2].t_str[j] != '\0' && vars->tok_error != 1)
	{
		if (j > 0)
		{
			if ((vars->tokens[vars->i2].t_str[j] == '>' && vars->tokens[vars->i2].t_str[j - 1] == '>') \
				&& ((is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j - 1) == NULL && \
				is_between_quotes(vars->tokens[vars->i2].t_str, '"', j - 1) == NULL) && \
				(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j) == NULL && \
				is_between_quotes(vars->tokens[vars->i2].t_str, '"', j) == NULL)))
			{
				start = j + 1;
				vars->tokens[vars->i2].out[index] = OUT_APPEND;
				skip_white_spaces(vars, &start, vars->i2);
				subs_outfile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i2].cmd[k++] = ' ';
			}
			else if (vars->tokens[vars->i2].t_str[j - 1] == '>' && \
						(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j - 1) == NULL && \
						is_between_quotes(vars->tokens[vars->i2].t_str, '"', j - 1) == NULL))
			{
				start = j;
				vars->tokens[vars->i2].out[index] = OUT_REDIRECT;
				skip_white_spaces(vars, &start, vars->i2);
				subs_outfile(vars, &start, index);
				index++;
				j = start;
				vars->tokens[vars->i2].cmd[k++] = ' ';
			}
			else
			{
				if (vars->tokens[vars->i2].t_str[j] != '>' || \
					(vars->tokens[vars->i2].t_str[j] == '>' && \
					(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j) != NULL \
					|| is_between_quotes(vars->tokens[vars->i2].t_str, '"', j) != NULL)))
					vars->tokens[vars->i2].cmd[k++] = vars->tokens[vars->i2].t_str[j];
				j++;
			}
		}
		else
		{
			if (vars->tokens[vars->i2].t_str[j] != '>' || \
				(vars->tokens[vars->i2].t_str[j] == '>' && \
				(is_between_quotes(vars->tokens[vars->i2].t_str, '\'', j) != NULL \
				|| is_between_quotes(vars->tokens[vars->i2].t_str, '"', j) != NULL)))
				vars->tokens[vars->i2].cmd[k++] = vars->tokens[vars->i2].t_str[j];
			j++;
		}
	}
	vars->tokens[vars->i2].cmd[k] = '\0';
}

void	find_outfile(t_prgm *vars)
{
	vars->i2 = 0;
	while (vars->i2 < vars->pipe_ct + 1)
	{
		free(vars->tokens[vars->i2].t_str);
		vars->tokens[vars->i2].t_str = ft_strdup(vars->tokens[vars->i2].cmd);
		free(vars->tokens[vars->i2].cmd);
		vars->tokens[vars->i2].cmd = malloc(sizeof(char) * (ft_strlen(vars->tokens[vars->i2].t_str) + 1));
		find_outfile_init(vars);
		extract_outfiles(vars);
		if (vars->tokens[vars->i2].out != NULL && vars->tokens[vars->i2].outfile == NULL)
		{
			printf("syntax error near unexpected token\n");
			vars->tok_error = 1;
		}
		vars->i2++;
	}
}
