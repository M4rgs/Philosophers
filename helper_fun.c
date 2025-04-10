/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:17 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/10 00:59:08 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_free_args(pthread_mutex_t *forks, t_philo *philo, int f, int num)
{
	int	i;

	i = 0;
	if (f == 0)
	{
		while (i < num)
		{
			pthread_join(philo[i].thread, NULL);
			i++;
		}
		free(forks);
		free(philo);
	}
	if (f == 1)
	{
		if (forks)
			free(forks);
		if (philo)
			free(philo);
		ft_putstr_fd("Error : <Allocation>\nFailed to allocate\n", 1);
		exit(1);
	}
}
