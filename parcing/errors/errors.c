/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:09:51 by aankote           #+#    #+#             */
/*   Updated: 2023/03/15 09:34:56 by aankote          ###   ########.fr       */
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

// int check_errors()
// {
    
// }