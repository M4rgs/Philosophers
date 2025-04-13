/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:10:10 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 04:08:41 by tamounir         ###   ########.fr       */
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
	infos->last_meal = timestamp();
	infos->start = timestamp();
	infos->has_ate = 0;
	infos->time = 0;
	infos->total_ate = 0;
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
	return (0);
}

void	death_checker(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((int)philo[i].infos->total_ate == philo[i].infos->num_philo)
		{
			//ft_dextroy_mutex(philo);
			//ft_free_args(forks, philo, 0);
			return ;
		}
		if ((size_t)timestamp() - philo[i].last_meal > \
			(unsigned long)philo->infos->to_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lu %d died\n", (size_t)timestamp() - \
				philo->infos->start, philo->id);
			//ft_dextroy_mutex(philo);
			//ft_free_args(forks, philo, 0);
			return ;
		}
		i = (i + 1) % philo->infos->num_philo;
		usleep(500);
	}
}

int	init_threads(t_infos *infos, pthread_mutex_t *forks, t_philo *philo)
{
	int				i;
	pthread_mutex_t	print;

	i = -1;
	if (pthread_mutex_init(&print, NULL) == -1)
		return (ft_free_args(forks, philo, 1));
	while (++i < infos->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) == -1)
			return (ft_free_args(forks, philo, 1));
	}
	i = -1;
	while (++i < infos->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].lfork = &forks[i];
		philo[i].rfork = &forks[(i + 1) % infos->num_philo];
		philo[i].print = &print;
		philo[i].infos = infos;
	}
	return (0);
}

int	launch_threads(t_infos *infos, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < infos->num_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_routine, &philo[i]) == -1)
			return (ft_free_args(forks, philo, 1));
	}
	return (0);
}
