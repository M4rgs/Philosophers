/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/10 00:55:33 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_infos
{
	int	to_die;
	int	num_philo;
	int	to_eat;
	int	to_sleep;
	int	must_eat;
}	t_infos;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}	t_philo;

int		ft_atoi(char *s);
void	ft_putstr_fd(char *s, int fd);
void	err_args(int f);
void	init_threads(t_infos *infos);
void	init_args(t_infos *infos, char **av);
void	ft_free_args(pthread_mutex_t *forks, t_philo *philos, int f, int num);

#endif