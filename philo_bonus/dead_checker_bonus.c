/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_checker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:25:37 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/11 18:10:11 by tamounir         ###   ########.fr       */
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
		if (timing(philo->infos) - last_eat > philo->infos->to_die)
		{
			printing(philo->infos, philo, "died", 1);
			exit(1);
		}
		ft_usleep(philo->infos->to_eat, philo->infos);
	}
	return (NULL);
}

void	sem_destroyy(t_infos *infos)
{
	sem_close(infos->forks);
	sem_close(infos->print);
	sem_close(infos->last_meal);
	sem_close(infos->count);
	sem_unlink("forks_sema");
	sem_unlink("print_sema");
	sem_unlink("last_meal_sema");
	sem_unlink("meal_count_sema");
	free(infos->philo);
	free(infos);
	exit(0);
}
