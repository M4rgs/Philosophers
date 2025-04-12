/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:05:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 22:23:19 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_routine(t_philo *philo, char *s)
{
	philo->infos->time = (size_t)timestamp();
	pthread_mutex_lock(philo->print);
	printf("%ld %d %s", (size_t)timestamp() - philo->infos->start, \
		philo->id, s);
	pthread_mutex_unlock(philo->print);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_routine(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->rfork);
		print_routine(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_routine(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->lfork);
		print_routine(philo, "has taken a fork\n");
	}
	print_routine(philo, "is eating\n");
	philo->infos->has_ate++;
	if (philo->infos->has_ate == philo->infos->must_eat)
		philo->infos->total_ate++;
	usleep(philo->infos->to_eat * 1000);
	philo->last_meal = (size_t)timestamp();
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = timestamp();
	while (1)
	{
		ft_eat(philo);
		print_routine(philo, "is sleeping\n");
		usleep(philo->infos->to_sleep);
		print_routine(philo, "is thinking\n");
	}
	return (NULL);
}
