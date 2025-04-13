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
		ft_putstr_fd("Error : <arguments>\n\
		 Params should be only numbers\n", 1);
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
	t_infos			*infos;
	pthread_t		*thread;
	t_philo			*philo;
	int				i;

	if (ac < 5 || ac > 6)
		return (err_args(1));
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (init_args(infos, av) == 1)
		return (ft_free_args(infos, 0, 0, 1));
	philo = (t_philo *)malloc(infos->num_philo * sizeof(t_philo));
	if (init_mutex(philo, infos) == 1)
		return (ft_free_args(infos, philo, 0, 1));
	thread = (pthread_t *)malloc(infos->num_philo * sizeof(pthread_t));
	if (!thread)
		return (ft_free_args(infos, philo, 0, 1));
	i = -1;
	while (++i < infos->num_philo)
	{
		pthread_create(&thread[i], NULL, ft_routine, philo + i);
		usleep(100);
	}
	death_checker(philo, infos);
	free(thread);
	return (0);
}
