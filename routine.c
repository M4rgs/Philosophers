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

static void	print_routine(t_philo *philo, unsigned long time, char *s)
{
	pthread_mutex_lock(philo->print);
	printf("%lu %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(philo->print);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->last_meal = timestamp();
	while (1)
	{
		pthread_mutex_lock(&philo->infos->dead_mutex);
		if (philo->infos->is_dead)
		{
			pthread_mutex_unlock(&philo->infos->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->infos->dead_mutex);
		pthread_mutex_lock(&philo->mutex[philo->id - 1]);
		print_routine(philo, real_time(philo), "has taken a fork");
		pthread_mutex_lock(&philo->mutex[philo->id % philo->infos->num_philo]);
		print_routine(philo, real_time(philo), "has taken a fork");
		print_routine(philo, real_time(philo), "is eating");
		philo->ate++;
		if (philo->ate == philo->infos->must_eat)
			philo->infos->total_ate++;
		usleep(philo->infos->to_eat * 1000);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->infos->num_philo]);
		print_routine(philo, real_time(philo), "is sleeping");
		usleep(philo->infos->to_sleep * 1000);
		print_routine(philo, real_time(philo), "is thinking");
	}
	return (0);
}

void	death_checker(t_philo *philo, t_infos *infos)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].infos->total_ate == philo[i].infos->num_philo)
		{
			dest_mutex(philo);
			ft_free_args(infos, philo, philo->mutex, 0);
			return ;
		}
		if (timestamp() - philo[i].last_meal > infos->to_die)
		{
			usleep(100);
			pthread_mutex_lock(&infos->dead_mutex);
			if (infos->is_dead == 0)
			{
				printf("%lu %d died\n", real_time(philo), philo->id);
				philo->infos->is_dead = 1;
			}
			pthread_mutex_unlock(&infos->dead_mutex);
			dest_mutex(philo);
			ft_free_args(infos, philo, 0, 0);
			return ;
		}
		i = (i + 1) % infos->num_philo;
		usleep(500);
	}
}
