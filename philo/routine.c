/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:05:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/24 06:07:46 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	taking_forks(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(&infos->dead_mutex), 1);
	pthread_mutex_unlock(&infos->dead_mutex);
	printingg(philo, infos, 1);
	pthread_mutex_lock(philo->rfork);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(philo->rfork),
			pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(&infos->dead_mutex), 1);
	pthread_mutex_unlock(&infos->dead_mutex);
	printingg(philo, infos, 1);
	return (0);
}

static int	eating(t_infos *infos, t_philo *philo)
{
	if (check_is_full(philo))
		return (1);
	pthread_mutex_lock(&infos->philo[philo->id - 1].last_meal);
	infos->philo[philo->id - 1].last_time_eat = timing();
	pthread_mutex_unlock(&infos->philo[philo->id - 1].last_meal);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(&infos->dead_mutex),
			pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(philo->rfork), 1);
	pthread_mutex_unlock(&infos->dead_mutex);
	printingg(philo, infos, 3);
	ft_usleep(infos->to_eat, infos);
	pthread_mutex_lock(&philo->count);
	philo->ate++;
	pthread_mutex_unlock(&philo->count);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_lock(&infos->full);
	if (infos->ending_flag == 1)
		return (pthread_mutex_unlock(&infos->full), 1);
	pthread_mutex_unlock(&infos->full);
	return (0);
}

static int	sleeping(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(&infos->dead_mutex), 1);
	pthread_mutex_unlock(&infos->dead_mutex);
	printingg(philo, infos, 2);
	ft_usleep(infos->to_sleep, infos);
	return (0);
}

static int	thinking(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(&infos->dead_mutex), 1);
	pthread_mutex_unlock(&infos->dead_mutex);
	printingg(philo, infos, 4);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_infos	*infos;

	philo = (t_philo *)arg;
	infos = philo->infos;
	if (infos->num_philo == 1)
		return (ft_one_philo(infos, philo));
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (taking_forks(infos, philo) == 1)
			return (NULL);
		if (eating(infos, philo) == 1)
			return (NULL);
		if (sleeping(infos, philo) == 1)
			return (NULL);
		if (thinking(infos, philo) == 1)
			return (NULL);
	}
	return (NULL);
}
