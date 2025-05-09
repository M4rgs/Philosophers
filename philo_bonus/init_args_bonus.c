/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:25:29 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/09 22:36:24 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_args(t_infos *infos, char **av)
{
	infos->num_philo = ft_atoi(av[1]);
	infos->to_die = ft_atoi(av[2]);
	infos->to_eat = ft_atoi(av[3]);
	infos->to_sleep = ft_atoi(av[4]);
	infos->must_eat = -1;
	if (av[5])
	{
		infos->must_eat = ft_atoi(av[5]);
		if (infos->must_eat <= 0)
			return (err_args(3));
	}
	if (infos->num_philo <= 0 || infos->to_die <= 0 || infos->to_eat <= 0
		|| infos->to_sleep <= 0)
	{
		return (err_args(3));
	}
	return (0);
}

int	init_data(t_infos *infos)
{
	size_t	i;

	i = -1;
	sem_unlink("forks_sema");
	sem_unlink("print_sema");
	sem_unlink("last_meal_sema");
	sem_unlink("meal_count_sema");
	infos->forks = sem_open("forks_sema", O_CREAT, 0644, infos->num_philo);
	infos->print = sem_open("print_sema", O_CREAT, 0644, 1);
	infos->last_meal = sem_open("last_meal_sema", O_CREAT, 0644, 1);
	infos->count = sem_open("meal_count_sema", O_CREAT, 0644, 1);
	if (!infos->forks || !infos->print || !infos->last_meal || !infos->count)
		return (1);
	infos->starting = timing();
	while (++i < infos->num_philo)
	{
		infos->philo[i].id = i + 1;
		infos->philo[i].ate = 0;
		infos->philo[i].pid = -1;
		infos->philo[i].last_time_eat = timing();
		infos->philo[i].infos = infos;
	}
	return (0);
}

int	proccess_init(t_infos *infos)
{
	size_t	i;

	i = -1;
	while (++i < infos->num_philo)
	{
		infos->philo[i].pid = fork();
		if (infos->philo[i].pid == 0)
			ft_routine(infos, &infos->philo[i]);
		else if (infos->philo[i].pid < 0)
			return (1);
	}
	return (0);
}
