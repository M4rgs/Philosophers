/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 07:51:22 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/15 00:59:57 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing(t_infos *infos, t_philo *philo, char *msg, int dead)
{
	size_t	time;

	time = timing(infos) - philo->infos->starting;
	sem_wait(infos->print);
	printf("%ld %d %s\n", time, philo->id, msg);
	if (dead == 0)
		sem_post(infos->print);
}

static int	args_checker(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	err_args(int f)
{
	if (f == 1)
	{
		ft_putstr_fd("Error : <arguments>\n Please try :\
		 num_philo time_die time_eat time_sleep (num_eat)\n", 1);
		return (1);
	}
	if (f == 2)
	{
		ft_putstr_fd("Error : <arguments>\n\
		 Params should be only numbers\n", 1);
		return (1);
	}
	if (f == 3)
	{
		ft_putstr_fd("Error : <arguments>\n Params should be\
		 > 0 && < INT_MAX\n", 1);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_infos	*infos;

	if (ac < 5 || ac > 6)
		return (err_args(1));
	if (args_checker(av) == 1)
		return (err_args(1));
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (1);
	if (init_args(infos, av))
		return (free(infos), 1);
	infos->philo = malloc(sizeof(t_philo) * infos->num_philo);
	if (!infos->philo)
		return (free(infos), 1);
	if (init_data(infos) == 1)
		return (kill_and_close(infos), 1);
	if (proccess_init(infos) == 1)
		return (kill_and_close(infos), 1);
	kill_and_close(infos);
	free(infos->philo);
	free(infos);
}
