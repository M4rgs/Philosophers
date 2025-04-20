/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:25:29 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/20 23:14:19 by tamounir         ###   ########.fr       */
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

void	init_procc(t_infos *infos)
{
	int	i;
	pid_t	pid;

	i = 0;
	sem_init(&infos->philo->sema, 0, 1);
	while (i < infos->num_philo)
	{
		pid = fork();
		if (pid == 0)
			
		
	}
}

void	init_data(t_infos *infos)
{
	size_t	i;

	i = -1;
	infos->starting = timing();
	infos->is_dead = 0;
	infos->total_ate = 0;
	while (++i < infos->num_philo)
	{
        infos->philo[i].pid = fork();
        if (infos->philo[i].pid == -1)
            return ;
        sem_init(&infos->philo[i].sema, 0, 1);
		infos->philo[i].id = i + 1;
		infos->philo[i].ate = 0;
		infos->philo[i].last_time_eat = timing();
		infos->philo[i].infos = infos;
	}
}
