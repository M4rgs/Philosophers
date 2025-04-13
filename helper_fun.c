/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:17 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 04:08:12 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	timestamp(void)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l);
}

unsigned long	real_time(t_philo *philo)
{
	return (timestamp() - philo->infos->time);
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
		if ((resu * signe > 2147483647 || resu * signe < -2147483648)
			|| (s[i] < '0' || s[i] > '9'))
		{
			err_args(2);
		}
		i++;
	}
	return (resu * signe);
}

int	ft_free_args(t_infos *infos, t_philo *philo, pthread_mutex_t *mutex, int f)
{
	if (infos)
		free(infos);
	if (mutex)
		free(mutex);
	if (philo)
		free(philo);
	return (f);
}
