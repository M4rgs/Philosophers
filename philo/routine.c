/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:05:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/08 16:53:29 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	taking_forks(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(&infos->dead_mutex),
			pthread_mutex_unlock(&infos->print), 1);
	printf("%lu %d has taken a fork\n", timing() - infos->starting, philo->id);
	pthread_mutex_unlock(&infos->dead_mutex);
	pthread_mutex_unlock(&infos->print);
	pthread_mutex_lock(philo->rfork);
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(philo->rfork),
			pthread_mutex_unlock(&infos->dead_mutex),
			pthread_mutex_unlock(&infos->print), 1);
	printf("%lu %d has taken a fork\n", timing() - infos->starting, philo->id);
	pthread_mutex_unlock(&infos->dead_mutex);
	pthread_mutex_unlock(&infos->print);
	return (0);
}

static int	eating(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->last_time_eat = timing();
	pthread_mutex_unlock(&philo->last_meal);
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(&infos->print),
			pthread_mutex_unlock(&infos->dead_mutex),
			pthread_mutex_unlock(philo->lfork),
			pthread_mutex_unlock(philo->rfork), 1);
	printf("%lu %d is eating\n", timing() - infos->starting, philo->id);
	pthread_mutex_unlock(&infos->dead_mutex);
	pthread_mutex_unlock(&infos->print);
	ft_usleep(infos->to_eat);
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
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(&infos->dead_mutex),
			pthread_mutex_unlock(&infos->print), 1);
	printf("%lu %d is sleeping\n", timing() - infos->starting, philo->id);
	pthread_mutex_unlock(&infos->dead_mutex);
	pthread_mutex_unlock(&infos->print);
	ft_usleep(infos->to_sleep);
	return (0);
}

static int	thinking(t_infos *infos, t_philo *philo)
{
	pthread_mutex_lock(&infos->print);
	pthread_mutex_lock(&infos->dead_mutex);
	if (infos->is_dead == 1)
		return (pthread_mutex_unlock(&infos->dead_mutex),
			pthread_mutex_unlock(&infos->print), 1);
	printf("%lu %d is thinking\n", timing() - infos->starting, philo->id);
	pthread_mutex_unlock(&infos->dead_mutex);
	pthread_mutex_unlock(&infos->print);
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
		ft_usleep(infos->to_eat);
	while (1)
	{
		if (taking_forks(infos, philo) == 1)
			return (NULL);
		if (check_is_full(philo) == 1)
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
