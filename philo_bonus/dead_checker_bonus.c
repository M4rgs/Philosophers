/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:25:37 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/30 01:53:14 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*is_dead(void *args)
{
	t_philo	*philo;
	size_t	last_eat;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->infos->last_meal);
		last_eat = philo->last_time_eat;
		sem_post(philo->infos->last_meal);
		if (timing() - last_eat > philo->infos->to_die)
		{
			printing(philo->infos, philo, "died", 1);
			exit(1);
		}
		ft_usleep(philo->infos->to_eat);
	}
	return (NULL);
}
