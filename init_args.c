/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:10:10 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/10 01:00:06 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_infos *infos, char **av)
{
	infos->num_philo = ft_atoi(av[1]);
	infos->to_die = ft_atoi(av[2]);
	infos->to_eat = ft_atoi(av[3]);
	infos->to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		infos->must_eat = ft_atoi(av[5]);
		if (infos->must_eat <= 0)
			err_args(3);
	}
	if (infos->num_philo <= 0 || infos->to_die <= 0 || infos->to_eat <= 0
		|| infos->to_sleep <= 0)
	{
		err_args(3);
	}
}

void	*ft_routine(void *t)
{
	(void)t;
	printf("ghggggg");
	return (NULL);
}

void	init_threads(t_infos *infos)
{
	int				i;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	i = 0;
	philo = malloc(infos->num_philo * sizeof(t_philo));
	forks = malloc(infos->num_philo * sizeof(pthread_mutex_t));
	if (!philo || !forks)
		ft_free_args(forks, philo, 1, 0);
	while (i < infos->num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < infos->num_philo)
	{
		philo[i].id = i;
		philo[i].lfork = &forks[i];
		philo[i].rfork = &forks[(i + 1) % infos->num_philo];
		pthread_create(&philo[i].thread, NULL, ft_routine, &philo[i]);
		i++;
	}
	ft_free_args(forks, philo, 0, infos->num_philo);
}
