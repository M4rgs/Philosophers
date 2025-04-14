/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:17 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/14 06:00:30 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timing(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("Error: gettimeofday :/ \n", 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(char *s)
{
	int		i;
	int		signe;
	long	resu;

	i = 0;
	signe = 1;
	resu = 0;
	while (s[i] == 32)
		i++;
	if ((s[i] == '-' || s[i] == '+') && s[i + 1] != '\0')
		signe = 44 - s[i++];
	while (s[i])
	{
		resu = resu * 10 + (s[i] - 48);
		if ((resu * signe > 2147483647 || resu * signe < -2147483648))
			return (-1);
		i++;
	}
	return (resu * signe);
}

int	ft_usleep(size_t ms, t_infos *infos)
{
	size_t	start;

	start = timing();
	while ((timing() - start) < ms)
	{
		pthread_mutex_lock(&infos->dead_mutex);
		if (infos->is_dead == 1)
			return (pthread_mutex_unlock(&infos->dead_mutex), 0);
		pthread_mutex_unlock(&infos->dead_mutex);
		usleep(500);
	}
	return (0);
}

void	ft_free_args(t_infos *infos)
{
	size_t	i;

	i = -1;
	while (++i < infos->num_philo)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		pthread_mutex_destroy(&infos->philo[i].last_meal);
		pthread_mutex_destroy(&infos->philo[i].count);
	}
	pthread_mutex_destroy(&infos->print);
	pthread_mutex_destroy(&infos->dead_mutex);
	pthread_mutex_destroy(&infos->full);
	free(infos->forks);
	free(infos->philo);
	free(infos);
}
