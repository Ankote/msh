/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:09:51 by aankote           #+#    #+#             */
/*   Updated: 2023/03/15 17:53:36 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pipe_errors(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    if(tmp->type == PIPE)
    {
        dep.exit_status = ERROR;
        return (0);
    }    
    while(tmp)
    {
        if(tmp->type == PIPE && !tmp->next)
        {
            dep.exit_status = ERROR;
            return (0);
        }  
        tmp = tmp->next;
    }
    return (1);
}

int is_opr(int type)
{
    if(type == TRUNC || type == APPEND)
        return (1);
    if(type == INPUT || type == HERDOC)
        return (1);
    if(type == PIPE)
        return (1);
    return(0);
}

int check_oper(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    while(tmp)
    {
        if(is_opr(tmp->type) && tmp->next && is_opr(tmp->next->type))
        {
            printf("syntax error near unexpected token %s\n", tmp->next->val);
            dep.exit_status = ERROR;
            return (0);
        }
        if(is_opr(tmp->type) && !tmp->next)
        {    
             printf("syntax error near unexpected token 'newline'\n");
             dep.exit_status = ERROR;
            return (0);
        }
        tmp = tmp->next;
    }
    return(1);
}

int  is_error_char(char c)
{
    if(c == '*' ||  c == ';' || c == '\\')
        return (1);
    return (0);
}

//we have to use this function befor do exoanting!!.

int  ft_error_char(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(is_error_char(str[i]) && (!quotes(str,  i)
            || quotes(str, i) == 1))
        {
            printf("SYNTAX ERROR!\n");
            dep.exit_status = ERROR;
            return (0);
        }
        i++;
    }
    return (1);
}

//function closedir  automaticlly will free dr
int check_command(char *str)
{
    DIR *dr;
    if(str && str[0] == '/')
    {
        if(!str[1])
            printf("bash: %s :is a directory\n", str);
        else
        {
            dr = opendir(str + 1);
            if(opendir(str + 1))
                printf("bash: %s :is a directory\n", str);
            if(dr)
                closedir(dr);
        }
        dep.exit_status = ERROR;
        return (0);
    }
    return (1);    
}