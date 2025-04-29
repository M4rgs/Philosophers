/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:46:09 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/29 04:35:42 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	taking_forks(t_infos *infos, t_philo *philo)
{
	sem_wait(infos->forks);
	sem_wait(infos->print);
	printf("%d has taken a fork\n", philo->id);
	sem_post(infos->print);
	sem_wait(infos->forks);
	sem_wait(infos->print);
	printf("%d hast taken a fork\n", philo->id);
	sem_post(infos->print);
}

void	is_eating(t_infos *infos, t_philo *philo)
{
	sem_wait(infos->print);
	printf("%d is eating\n", philo->id);
	sem_post(infos->print);
	sem_post(infos->forks);
	sem_post(infos->forks);
	sem_wait(infos->last_meal);
	philo->last_time_eat = timing();
	sem_post(infos->last_meal);
	ft_usleep(infos->to_eat);
	sem_wait(infos->count);
	philo->ate++;
	sem_post(infos->count);
}

void	is_sleeping(t_infos *infos, t_philo *philo)
{
	sem_wait(infos->print);
	printf("%d is sleeping\n", philo->id);
	sem_post(infos->print);
	ft_usleep(infos->to_sleep);
}

void	is_thinking(t_infos *infos, t_philo *philo)
{
	sem_wait(infos->print);
	printf("%d is thinking\n", philo->id);
	sem_post(infos->print);
}

void	ft_routine(t_infos *infos, t_philo *philo)
{
	infos->index = philo->id - 1;
	pthread_create(&infos->thread, NULL, monitor, infos);
	pthread_detach(infos->thread);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		taking_forks(infos, philo);
		is_eating(infos, philo);
		is_sleeping(infos, philo);
		is_thinking(infos, philo);
	}
	exit(0);
}
