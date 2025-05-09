/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:07:46 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/08 18:36:18 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		 num_philo time_die time_eat time_sleep (num_eat)\n", 2);
		return (1);
	}
	if (f == 2)
	{
		ft_putstr_fd("Error : <arguments>\n\
		 Params should be only numbers\n", 2);
		return (1);
	}
	if (f == 3)
	{
		ft_putstr_fd("Error : <arguments>\n Params should be\
		 > 0 && < INT_MAX\n", 2);
		return (1);
	}
	if (f == 4)
	{
		ft_putstr_fd("Error: <UP_MAX threads not allowed>\n ", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_infos			*infos;

	if (ac < 5 || ac > 6)
		return (err_args(1));
	if (args_checker(av) == 1)
		return (err_args(1));
	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (1);
	if (init_args(infos, av))
		return (free(infos), 1);
	infos->forks = malloc(sizeof(pthread_mutex_t) * infos->num_philo);
	if (!infos->forks)
		return (free(infos), 1);
	infos->philo = malloc(sizeof(t_philo) * infos->num_philo);
	if (!infos->philo)
		return (free(infos->forks), free(infos), 1);
	init_data(infos);
	if (launch_threads(infos) == 1)
		return (ft_free_args(infos), 1);
	ft_free_args(infos);
	return (0);
}
