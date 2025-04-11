/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:07:46 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 04:06:51 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	err_args(int f)
{
	if (f == 1)
	{
		ft_putstr_fd("Error : <arguments>\n Please try :\
		 num_philo ime_die time_eat time_sleep (num_eat)\n", 1);
		return (1);
	}
	if (f == 2)
	{
		ft_putstr_fd("Error : <arguments>\n Params should be only numbers\n", 1);
		return (1);
	}
	if (f == 3)
	{
		ft_putstr_fd("Error : <arguments>\n Params should be > 0\n", 1);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_infos			infos;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6)
		return (err_args(1));
	if (init_args(&infos, av) == 1)
		return (1);
	philo = malloc(infos.num_philo * sizeof(t_philo));
	forks = malloc(infos.num_philo * sizeof(pthread_mutex_t));
	if (!forks || !philo)
		return (ft_free_args(forks, philo, 1));
	if (init_threads(&infos, forks, philo) == 1)
		return (1);
	if (launch_threads(&infos, forks, philo) == 1)
		return (1);
	ft_free_args(forks, philo, 0);
}
