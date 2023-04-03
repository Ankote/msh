/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:24:00 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/13 15:46:35 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

void	is_numeric(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[0][j])
		{
			if ((args[0][0] == '-' || args[0][0] == '+') && args[0][1] == '0'
			&& !ft_atoi(&args[0][1]))
				(printf("exit\n"), exit(0));
			if (args[0][j] != '0' && !ft_atoi(&args[0][j]))
			{
				write(2, "minishell: exit: ", 17);
				write(2, args[0], ft_strlen(args[0]));
				write(2, ": numeric argument required\n", 28);
				exit(255);
			}
			j++;
		}
		i++;
	}
}

int	ft_exit(t_list *data)
{
	long long	len;
	len = count_args(data->args);
	// printf("%s", data->args[0]);
	if (!data->args[0])
		(printf("exit\n"), exit(0));
	is_numeric(data->args);
	// write(2, &len, 4);
	if (len > 2)
		write(2, "exit\nminishell: exit: too many arguments\n", 41);
	else if (len == 2)
	{
		len = ft_atoi(data->args[0]);
		if (data->args[0][0] != '-' && len < 0)
		{
			write(2, "minishell: exit: ", 17);
			write(2, data->args[0], ft_strlen(data->args[0]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else
			(printf("exit\n"), exit(ft_atoi(data->args[0])));
	}
	return (1);
}
