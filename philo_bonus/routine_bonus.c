/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:46:09 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/15 03:52:43 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	is_eating(t_infos *infos, t_philo *philo)
{
	size_t	meals;

	meals = 0;
	sem_wait(infos->forks);
	printing(infos, philo, "has taken a fork", 0);
	sem_wait(infos->forks);
	printing(infos, philo, "has taken a fork", 0);
	sem_wait(infos->last_meal);
	philo->last_time_eat = timing(infos);
	sem_post(infos->last_meal);
	printing(infos, philo, "is eating", 0);
	sem_wait(infos->count);
	philo->ate++;
	sem_post(infos->count);
	ft_usleep(infos->to_eat, infos);
	sem_post(infos->forks);
	sem_post(infos->forks);
	sem_wait(philo->infos->count);
	meals = philo->ate;
	sem_post(philo->infos->count);
	if (meals == philo->infos->must_eat)
		exit(0);
}

static void	is_sleeping(t_infos *infos, t_philo *philo)
{
	printing(infos, philo, "is sleeping", 0);
	ft_usleep(infos->to_sleep, infos);
}

static void	is_thinking(t_infos *infos, t_philo *philo)
{
	printing(infos, philo, "is thinking", 0);
}

void	ft_routine(t_infos *infos, t_philo *philo)
{
	infos->index = philo->id - 1;
	if (pthread_create(&infos->thread, NULL, is_dead, philo) == -1)
		exit(1);
	if (pthread_detach(infos->thread) == -1)
		exit(1);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		is_eating(infos, philo);
		is_sleeping(infos, philo);
		is_thinking(infos, philo);
	}
	exit(0);
}
