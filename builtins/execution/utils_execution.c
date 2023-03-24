/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:21:32 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/24 00:19:37 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_builtin(t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(list->args[0], "echo"))
		echo(dep.env, list);
	else if (!ft_strcmp(list->args[0], "pwd"))
		printf("%s\n", dep.pwd);
	else if (!ft_strcmp(list->args[0], "exit"))
		ft_exit(list);
	else if (!ft_strcmp(list->args[0], "cd"))
		ft_cd(list);
	else if (!ft_strcmp(list->args[0], "env"))
		ft_env();
	else if (!ft_strcmp(list->args[0], "unset"))
		ft_unset(list);
	else if (!ft_strcmp(list->args[0], "export"))
		ft_export(list);
	else
		i++;
	return (i);
}

char	*get_arg(void)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dep.env[i])
	{
		if (dep.env[i][j] == 'P' && dep.env[i][j + 4] == '=')
		{
			str = dep.env[i];
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	ft_next_exec(t_list *list, int *stdin)
{
	int	fd[2];

	*stdin = dup(0);
	while (list)
	{
		pipe(fd);
		if (fork() == 0)
		{
			close(fd[0]);
			if (list->next)
				dup2(1,fd[1] );
			else
				dup2( 1,list->outfile);
			close(fd[1]);
			if (!check_command(list->args[0]))
				return ;
			str_tolower(list->args[0]);
			if (check_if_builtin(list) == 1)
				main_execution(list);
		}
		if (list->infile != 0)
			dup2(list->infile, 0);
		else
			dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		list = list->next;
	}
}

void	ft_exec(t_list *list)
{
	int	stdin;

	if (ft_listsize(list) == 1)
	{
		if (!check_command(list->args[0]))
			return ;
		str_tolower(list->args[0]);
		if (check_if_builtin(list) == 1)
		{
			if (fork() == 0)
				main_execution(list);
			while (wait(NULL) != -1)
				;
		}
	}
	else
	{
		ft_next_exec(list, &stdin);
		while (wait(NULL) != -1)
			;
		dup2(stdin, 0);
	}
}
