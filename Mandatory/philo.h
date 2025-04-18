/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/18 20:56:35 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_infos
{
	size_t			num_philo;
	size_t			to_die;
	size_t			to_sleep;
	size_t			to_eat;
	size_t			must_eat;
	size_t			total_ate;
	size_t			starting;
	size_t			is_dead;
	size_t			ending_flag;
	pthread_mutex_t	full;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	pthread_t		death_checker;
}	t_infos;

typedef struct s_philo
{
	int				id;
	size_t			ate;
	size_t			last_time_eat;
	pthread_t		id_thre;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	count;
	t_infos			*infos;
}	t_philo;

int				ft_atoi(char *s);
void			ft_putstr_fd(char *s, int fd);
int				err_args(int f);
int				init_args(t_infos *infos, char **av);
void			init_data(t_infos *infos);
int				launch_threads(t_infos *infos);
void			*ft_routine(void *arg);
void			ft_one_philo(t_infos *infos, t_philo *philo);
void			*death_checker(t_infos *infos);
size_t			timing(void);
int				ft_usleep(size_t milliseconds, t_infos *args);
void			ft_free_args(t_infos *infos);

#endif