/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:10:10 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/15 00:52:35 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_infos *infos, char **av)
{
	infos->num_philo = ft_atoi(av[1]);
	infos->to_die = ft_atoi(av[2]);
	infos->to_eat = ft_atoi(av[3]);
	infos->to_sleep = ft_atoi(av[4]);
	infos->must_eat = -1;
	if (av[5])
	{
		infos->must_eat = ft_atoi(av[5]);
		if (infos->must_eat <= 0)
			return (err_args(3));
	}
	if (infos->num_philo <= 0 || infos->to_die <= 0 || infos->to_eat <= 0
		|| infos->to_sleep <= 0)
	{
		return (err_args(3));
	}
	if (infos->num_philo > 200)
		return (err_args(4));
	infos->last_time_eat = timing();
	{
		if (infos->last_time_eat == 0)
			return (1);
	}
	return (0);
}

void	init_data(t_infos *infos)
{
	size_t	i;

	i = -1;
	pthread_mutex_init(&infos->print, NULL);
	pthread_mutex_init(&infos->dead_mutex, NULL);
	pthread_mutex_init(&infos->full, NULL);
	pthread_mutex_init(&infos->last_meal, NULL);
	infos->starting = timing();
	infos->is_dead = 0;
	infos->ending_flag = 0;
	while (++i < infos->num_philo)
	{
		infos->philo[i].id = i + 1;
		infos->philo[i].ate = 0;
		infos->philo[i].is_full = 0;
		infos->philo[i].last_time_eat = timing();
		infos->philo[i].rfork = &infos->forks[i];
		infos->philo[i].lfork = &infos->forks[(i + 1) % infos->num_philo];
		infos->philo[i].infos = infos;
		pthread_mutex_init(&infos->philo[i].count, NULL);
		pthread_mutex_init(&infos->philo[i].last_meal, NULL);
		pthread_mutex_init(&infos->forks[i], NULL);
	}
}

int	launch_threads(t_infos *infos)
{
	size_t	i;

	i = -1;
	while (++i < infos->num_philo)
	{
		if (pthread_create(&infos->philo[i].id_thre, \
			NULL, ft_routine, &infos->philo[i]))
			return (1);
	}
	i = -1;
	if (pthread_create(&infos->death_checker, \
		NULL, monitor, infos))
		return (1);
	while (++i < infos->num_philo)
	{
		if (pthread_join(infos->philo[i].id_thre, NULL) != 0)
			return (1);
	}
	if (pthread_join(infos->death_checker, NULL))
		return (1);
	return (0);
}

void	ft_free_args(t_infos *infos)
{
	size_t	i;

	i = -1;
	while (++i < infos->num_philo)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		pthread_mutex_destroy(&infos->philo[i].last_meal);
		pthread_mutex_destroy(&infos->philo[i].count);
	}
	pthread_mutex_destroy(&infos->print);
	pthread_mutex_destroy(&infos->dead_mutex);
	pthread_mutex_destroy(&infos->full);
	pthread_mutex_destroy(&infos->last_meal);
	if (infos->philo)
		free(infos->philo);
	if (infos->forks)
		free(infos->forks);
	if (infos)
		free(infos);
}
