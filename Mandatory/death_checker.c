/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 04:06:03 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/20 23:58:01 by tamounir         ###   ########.fr       */
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

static void	set_as_finished(t_infos *infos)
{
	pthread_mutex_lock(&infos->full);
	infos->ending_flag = 1;
	pthread_mutex_unlock(&infos->full);
}

void	*death_checker(t_infos *infos)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < infos->num_philo)
		{
			pthread_mutex_lock(&infos->philo[i].count);
			if (infos->must_eat <= infos->philo[i].ate)
			{
				infos->total_ate++;
				if (infos->total_ate >= infos->num_philo)
					return (pthread_mutex_unlock(&infos->philo[i].count),
						set_as_finished(infos), NULL);
				else
					pthread_mutex_unlock(&infos->philo[i].count);
			}
			else
				pthread_mutex_unlock(&infos->philo[i].count);
			if (is_dead(infos, &infos->philo[i]))
				return (NULL);
		}
	}
	return (NULL);
}

void	ft_one_philo(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	printf("%lu %d has taken a fork\n", timing() - infos->starting, philo->id);
	infos->is_dead = 1;
	pthread_mutex_unlock(&infos->print);
	pthread_mutex_unlock(&infos->dead_mutex);
}
