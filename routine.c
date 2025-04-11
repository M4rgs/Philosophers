/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:05:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 04:09:19 by tamounir         ###   ########.fr       */
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
	pthread_mutex_lock(philo->print);
	printf("philo number %d %s", philo->id, s);
	pthread_mutex_unlock(philo->print);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		while (1)
		{
			pthread_mutex_lock(philo->rfork);
			print_routine(philo, "has taken a fork 1\n");
			pthread_mutex_lock(philo->lfork);
			print_routine(philo, "has taken a fork 2\n");
			print_routine(philo, "is eating\n");
			usleep(philo->infos->to_eat * 1000);
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(philo->lfork);
			print_routine(philo, "is sleeping\n");
			usleep(philo->infos->to_sleep);
			print_routine(philo, "is thinking\n");
		}
	}
	else
	{
		while (1)
		{
			pthread_mutex_lock(philo->lfork);
			print_routine(philo, "has taken a fork 1\n");
			pthread_mutex_lock(philo->rfork);
			print_routine(philo, "has taken a fork 2\n");
			print_routine(philo, "is eating\n");
			philo->infos->last_meal = timestamp();
			usleep(philo->infos->to_eat * 1000);
			pthread_mutex_unlock(philo->lfork);
			pthread_mutex_unlock(philo->rfork);
			print_routine(philo, "is sleeping\n");
			usleep(philo->infos->to_sleep);
			print_routine(philo, "is thinking\n");
		}
	}
	return (NULL);
}
