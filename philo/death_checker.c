/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 04:06:03 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/05 06:06:14 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	if (timing() - philo->last_time_eat >= infos->to_die)
	{
		pthread_mutex_lock(&infos->print);
		pthread_mutex_lock(&infos->dead_mutex);
		infos->is_dead = 1;
		pthread_mutex_unlock(&infos->dead_mutex);
		printf("%zu %d died\n", timing() - infos->starting, philo->id);
		pthread_mutex_unlock(&infos->print);
		pthread_mutex_unlock(&philo->last_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal);
	return (0);
}

static int	is_hungry(t_infos *infos, t_philo *philo, size_t *total_ate)
{
	pthread_mutex_lock(&philo->count);
	if (infos->must_eat <= philo->ate \
		&& philo->is_full == 0)
	{
		philo->is_full = 1;
		*total_ate += 1;
		if (*total_ate >= infos->num_philo)
		{
			pthread_mutex_unlock(&philo->count);
			pthread_mutex_lock(&infos->full);
			infos->ending_flag = 1;
			pthread_mutex_unlock(&infos->full);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->count);
	return (0);
}

void	*monitor(void *arg)
{
	size_t	i;
	size_t	total_ate;
	t_infos	*infos;

	infos = (t_infos *)arg;
	total_ate = 0;
	while (1)
	{
		i = 0;
		while (i < infos->num_philo)
		{
			if (is_hungry(infos, &infos->philo[i], &total_ate))
				return (NULL);
			if (is_dead(infos, &infos->philo[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	*ft_one_philo(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	pthread_mutex_lock(philo->lfork);
	printf("%lu %d has taken a fork\n", timing() - infos->starting, philo->id);
	infos->is_dead = 1;
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(&infos->print);
	pthread_mutex_unlock(&infos->dead_mutex);
	return (NULL);
}

int	check_is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->count);
	if (philo->is_full == 1)
	{
		return (pthread_mutex_unlock(&philo->count),
			pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(philo->rfork), 1);
	}
	pthread_mutex_unlock(&philo->count);
	return (0);
}
