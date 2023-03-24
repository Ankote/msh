/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:03:56 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/17 15:07:36 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	int	i;

	i = 0;
	if (!dep.env)
		printf("env: No such file or directory\n");
	while (dep.env[i])
	{
		printf ("%s\n", dep.env[i]);
		i++;
	}
}
