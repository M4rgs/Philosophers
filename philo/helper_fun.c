/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:17 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/25 05:25:11 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timing(void)
{
	struct timeval		current_time;
	unsigned long long	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time);
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
		usleep(100);
	}
	return (0);
}

void	printingg(t_philo *philo, t_infos *infos, int f)
{
	pthread_mutex_lock(&infos->print);
	if (f == 1)
		printf("%lu %d has taken a fork\n", \
			timing() - infos->starting, philo->id);
	if (f == 2)
		printf("%lu %d is sleeping\n", timing() - infos->starting, philo->id);
	if (f == 3)
		printf("%lu %d is eating\n", timing() - infos->starting, philo->id);
	if (f == 4)
		printf("%lu %d is thinking\n", timing() - infos->starting, philo->id);
	pthread_mutex_unlock(&infos->print);
}
