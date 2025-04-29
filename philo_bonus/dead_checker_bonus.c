/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:25:37 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/29 04:36:12 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_infos *infos, t_philo *philo)
{
	sem_wait(infos->last_meal);
	if (get_time() - philo->last_time_eat >= infos->to_die)
	{
		printf("%zu %d died\n", get_time() - infos->starting, philo->id);
		sem_post(infos->last_meal);
		return (1);
	}
	sem_post(infos->last_meal);
	return (0);
}

void	*monitor(void *argss)
{
	t_infos	*infos;

	infos = (t_infos *)argss;
	while (1)
	{
		usleep(100);
		sem_wait(infos->count);
		if (infos->philo[infos->index].ate >= infos->must_eat)
		{
			sem_post(infos->count);
			exit(0);
		}
		sem_post(infos->count);
		if (is_dead(infos, infos->philo + infos->index))
			exit(1);
	}
	return (NULL);
}
