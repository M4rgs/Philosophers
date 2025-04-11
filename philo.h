/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 22:04:55 by tamounir         ###   ########.fr       */
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
	size_t	to_die;
	int		num_philo;
	int		to_eat;
	int		has_ate;
	int		to_sleep;
	int		must_eat;
	size_t	last_meal;
	size_t	start;
}	t_infos;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_infos			*infos;
	pthread_mutex_t	*print;
	long			died;
}	t_philo;

int		ft_atoi(char *s);
void	ft_putstr_fd(char *s, int fd);
int		err_args(int f);
int		init_threads(t_infos *infos, pthread_mutex_t *forks, t_philo *philo);
int		init_args(t_infos *infos, char **av);
int		ft_free_args(pthread_mutex_t *forks, t_philo *philo, int f);
void	*ft_routine(void *arg);
long	timestamp(void);
void	ft_eat(t_philo *philo);
int		launch_threads(t_infos *infos, pthread_mutex_t *forks, t_philo *philo);

#endif