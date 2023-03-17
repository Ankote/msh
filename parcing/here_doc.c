/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:46:24 by aankote           #+#    #+#             */
/*   Updated: 2023/03/17 14:51:39 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int do_exp_inp(char *limiter)
{
	int i;

	i = -1;
	while(limiter[++i])
	{
		if(limiter[i] == '\'' || limiter[i] == '\"')
			return (0);
	}
	return (1);
}

char  *exp_limiter(char *limiter)
{
	int i;
	char *p;

	i = -1;
	p = ft_strdup("");
	while(limiter[++i])
	{
		if(!quotes(limiter, i) )
		{
			if(limiter[i] != '\'' && limiter[i] != '\"')
				p = ft_charjoin(p, limiter[i]);
		}
		else
			p = ft_charjoin(p, limiter[i]);
	}
	return (p);
}

void here_doc(t_list *list, char *limiter, char **env)
{
    char *buffer;
	int fd;

	fd = open("tmp", O_TRUNC | O_CREAT |  O_RDWR, 0777);
	while(1)
	{
		buffer = get_next_line(0);
		if(!ft_strncmp(buffer, exp_limiter(limiter), ft_strlen(buffer) - 1))
		{
			free(buffer);
			return ;
		}
		if(do_exp_inp(limiter))
            buffer = ft_herd_exp(env, buffer, dep.exit_status);
		ft_putstr_fd(buffer, fd);
		list->infile = fd;
	}
}