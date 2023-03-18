/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:56:34 by aankote           #+#    #+#             */
/*   Updated: 2023/03/17 21:32:17 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft(int c)
{
	if (c == CMD)
		printf("CMD ");
	if (c == ARG)
		printf("ARG ");
	if (c == TRUNC)
		printf("TRUNC ");
	if (c == APPEND)
		printf("APPEND ");
	if (c == INPUT)
		printf("INPUT ");
	if (c == PIPE)
		printf("PIPE ");
	if (c == INFILE)
		printf("INFILE ");
	if (c == OUTFILE)
		printf("OUTFILE ");
	if (c == HERDOC)
		printf("HERDOC ");
	if (c == LIMITER)
		printf("LIMITER ");
}
//lesks checked : done
void	tokens(char *line, t_token **token, char **env)
{
	t_token	*tmp;

	get_token(line, token);
	tmp = *token;
	while (tmp)
	{
		type_arg(tmp); 
		if(tmp->type == INFILE || tmp->type == OUTFILE)
			tmp->val = ft_expand(env, tmp->val, dep.exit_status);
		tmp = tmp->next;
	}
}

//lesks checked : done

void expand_list(char **env, t_list **list, int sta)
{
	t_list *tmp;
	int i;
	i = -1;
	tmp = *list;
	while(tmp)
	{
		if(tmp->cmd)
			tmp->cmd = ft_expand(env, tmp->cmd,sta);
		if(tmp->args)
		{
			while(tmp->args[++i])
				tmp->args[i] = ft_expand(env, tmp->args[i],sta);
		}
		i = -1;
		tmp = tmp->next;
	}
}

void ft_free_token(t_token **list)
{
	t_token *tmp;
	
	while(*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void ft_free_list(t_list *list)
{
	if(list->cmd)
		free(list->cmd);
	if(list->args)
		free_double(list->args);
	list = NULL;
}

void ft_ck(t_list **lst)
{
	t_list *tmp;
	 tmp = *lst;
	while(tmp)
	{
		printf("%d", tmp->infile);
		if(tmp->infile == -1)
		{
			printf("error");
			return;
		}
		tmp = tmp->next;
	}
	
	
}

void		ft_next(char *line, t_token *data, char **env, t_list *list)
{
	int	i;

	i = 0;

	tokens(line, &data, env);
	if(!check_oper(&data))
	{
		return;
	}
	get_cmd(&list, &data);
	expand_list(env, &list, 125);
	while (list)
	{
		i = -1;
		if(list->cmd)
		{
			if(!check_command(list->cmd))
				return;
			str_tolower(list->cmd);
			if (!ft_strcmp(list->cmd, "echo"))
				echo(env, list);
			else if (!ft_strcmp(list->cmd, "pwd"))
			{
				expaned_arg(env, "$PWD", dep.exit_status);
				printf("\n");
			}
			else if (!ft_strcmp(list->cmd, "exit"))
			{
				ft_exit(list);
			}
			ft_free_list(list);
		}
		(list) = (list)->next;
	}
	free (line);
}


int	main(int ac, char **av, char **env)
{
	t_token	*data;
	t_list	*list;
	char	*line;

	data = malloc(sizeof(data));
	list = NULL;
	(void)ac;
	(void)av;
	dep.env = env;
	while (1)
	{
		line = readline("\x1b[1m\x1b[33mminishell$ \033[0m");
		if (!check_single_quotes(line))
		{ 
			printf("Syntax Error!\n");
			dep.exit_status = ERROR;
			continue ;
		}
		add_history(line);
		ft_next(line, data, env, list);
		dep.exit_status = SUCCESS;
	}
}

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
// 	(void)av;
// 	here_doc("\'l\'", env);
// }