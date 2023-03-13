/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:53:31 by aankote           #+#    #+#             */
/*   Updated: 2023/03/13 20:46:10 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*env[i][len] == '=' for handel if you put var like (US) th result will be "aankoteER=aankote"*/
char *get_value(char **env, char *var)
{
    int i;

    i = -1;
    int len;
    
    len = ft_strlen(var);
    while(env[++i] && var[0])
    {
        if(!ft_strncmp(env[i], var, len) && env[i][len + 1]
            && env[i][len] == '=')
            return(env[i] + len + 1);
    }
    return(ft_strdup(""));
}

char *ft_get_arg(char **env, char *str, int *i, int sta)
{
    char *p;
    
    p = ft_strdup("");
    if(!ft_isalnum(str[*i + 1]) && str[(*i + 1)] != '?')
    {
        
        p = ft_charjoin(p, str[(*i)++]);
        while(str[*i] && str[*i] != '$')
             p = ft_charjoin(p, str[*i++]);
        if(str[*i] == '$')
             p = ft_charjoin(p, str[*i++]);
        return(p);
    }
    if(str[(*i + 1)] == '?')
    {
        (*i) ++;
        return(ft_strdup(ft_itoa(sta)));
    }  
    while(str[++(*i)] && ft_isalnum(str[*i]))
    {
         p = ft_charjoin(p, str[*i]);
    }
    (*i)--;
    return(get_value(env, p));
}

char *ft_expand(char **env, char *str, int sta)
{
    int i;
    char *p;

    i = -1;
    p = ft_strdup("");
    while(str[++i])
    {
        if(str[i] == '$' && (quotes(str, i) == 0 || quotes(str, i) == 1))
            p = ft_strjoin(p, ft_get_arg(env, str, (&i), sta)); 
        else
        {
            if((str[i] != '\'' && str[i] != '\"'))
                p = ft_charjoin(p, str[i]);
            if(str[i] == '\'' && quotes(str, i) == 1)
                p = ft_charjoin(p, str[i]);
            if(str[i] == '\"' && quotes(str, i) == 2)
                p = ft_charjoin(p, str[i]);
        }
    }
    return (p);
}
