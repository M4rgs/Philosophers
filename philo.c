/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:07:46 by tamounir          #+#    #+#             */
/*   Updated: 2025/03/11 15:32:00 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_pthread(t_philo *philo)
{
	pthread_mutex_init(philo->mutex, NULL);
}

void	init_args(t_philo *philo, char **av)
{
	philo->philos = ft_atoi(av[1]);
	philo->time.to_die = ft_atoi(av[2]);
	philo->time.to_eat = ft_atoi(av[3]);
	philo->time.to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->time.must_eat = ft_atoi(av[5]);
	else
		philo->time.must_eat = -1;
	if (philo->philos <= 0 || philo->time.to_die <= 0 || philo->time.to_eat <= 0
		|| philo->time.to_sleep <= 0)
	{
		ft_putstr_fd("Error: Args\n", 2);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		init_args(&philo, av);
		init_pthread(&philo);
	}
}
