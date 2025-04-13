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
	if (infos == NULL)
		return (1);
	infos->num_philo = ft_atoi(av[1]);
	infos->to_die = ft_atoi(av[2]);
	infos->to_eat = ft_atoi(av[3]);
	infos->to_sleep = ft_atoi(av[4]);
	infos->time = timestamp();
	infos->must_eat = -1;
	infos->total_ate = 0;
	infos->is_dead = 0;
	pthread_mutex_init(&infos->dead_mutex, NULL);
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

static void	init_params(t_philo *philo, t_infos *infos, \
	pthread_mutex_t *mutex, pthread_mutex_t *pon)
{
	int	i;

	i = 0;
	while (i < infos->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].ate = 0;
		philo[i].mutex = mutex;
		philo[i].print = pon;
		philo[i].infos = infos;
		i++;
	}
}

int	init_mutex(t_philo *philo, t_infos *infos)
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	pon;
	int				i;

	i = 0;
	if (!philo)
		return (1);
	mutex = malloc(sizeof(pthread_mutex_t) * infos->num_philo);
	if (!mutex)
		return (ft_free_args(infos, philo, mutex, 1));
	while (i < infos->num_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL) == 1)
			return (ft_free_args(infos, philo, mutex, 1));
		i++;
	}
	if (pthread_mutex_init(&pon, NULL))
		return (ft_free_args(infos, philo, mutex, 1));
	init_params(philo, infos, mutex, &pon);
	free(mutex);
	return (0);
}

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->infos->num_philo)
		pthread_mutex_destroy(&philo->mutex[i++]);
}
