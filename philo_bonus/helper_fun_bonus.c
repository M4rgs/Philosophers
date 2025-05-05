/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 07:54:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/02 03:28:30 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = timing();
	while ((timing() - start) < ms)
		usleep(500);
	return (0);
}

void	kill_and_close(t_infos *infos)
{
	size_t	i;
	int		status;

	status = 0;
	i = -1;
	while (++i < infos->num_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
		{
			i = -1;
			while (++i < infos->num_philo)
				kill(infos->philo[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(infos->forks);
	sem_close(infos->print);
	sem_close(infos->last_meal);
	sem_close(infos->count);
	sem_unlink("forks_sema");
	sem_unlink("print_sema");
	sem_unlink("last_meal_sema");
	sem_unlink("meal_count_sema");
}
