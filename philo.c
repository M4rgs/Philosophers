/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:07:46 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/10 06:22:47 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	err_args(int f)
{
	if (f == 1)
	{
		ft_putstr_fd("Error : <arguments>\n Please try :\
		 num_philo ime_die time_eat time_sleep (num_eat)\n", 1);
		exit(1);
	}
	if (f == 2)
	{
		ft_putstr_fd("Error : <arguments>\n Params should be only numbers\n", 1);
		exit(1);
	}
	if (f == 3)
	{
		ft_putstr_fd("Error : <arguments>\n Params should be > 0\n", 1);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_infos			infos;

	if (ac < 5 || ac > 6)
		err_args(1);
	init_args(&infos, av);
	init_threads(&infos);
}
