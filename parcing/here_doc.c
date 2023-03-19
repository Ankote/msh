/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:46:24 by aankote           #+#    #+#             */
/*   Updated: 2023/03/19 15:09:09 by aankote          ###   ########.fr       */
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

char *check_name()
{
	int i;
	char *name;

	i = 0;
	name = ft_itoa(i);
	while(!access(name, F_OK))
	{
		free(name);
		name = ft_itoa(++i);
	}
	return(name);
}
void unlink_files(t_file *files)
{
	int i;

	i = 0;
	if(files->f_name)
	{
		while(files->f_name[i])
		{
			unlink(files->f_name[i]);
			free(files->f_name[i]);
			i++;
		}
	}
}

int  here_doc(char *limiter, char **env)
{
    char *buffer;
	int fd;
	int i;
	char *name;
	
	i = 0;
	name = check_name();
	fd = open(name, O_TRUNC | O_CREAT |  O_RDWR, 0777);
	free(name);
	while(1 && fd != -1)
	{
		buffer = get_next_line(0);
		if(!ft_strncmp(buffer, exp_limiter(limiter), ft_strlen(buffer) - 1))
		{
			free(buffer);
			return (fd);
		}
		if(do_exp_inp(limiter))
            buffer = ft_herd_exp(env, buffer, dep.exit_status);
		ft_putstr_fd(buffer, fd);
	}
	return(fd);
}
