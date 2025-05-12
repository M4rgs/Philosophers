/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:17 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/12 19:20:59 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timing(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("gettimeofday() error\n");
		return (0);
	}
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

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = timing();
	while ((timing() - start) < ms)
		usleep(500);
	return (0);
}
