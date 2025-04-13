/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/11 22:16:15 by tamounir         ###   ########.fr       */
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
	int				num_philo;
	unsigned long	to_die;
	int				to_eat;
	int				to_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}	t_infos;

typedef struct s_philo
{
	int				ate;
	int				id;
	t_infos			*infos;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	unsigned long	last_meal;
}	t_philo;

int				ft_atoi(char *s);
void			ft_putstr_fd(char *s, int fd);
int				err_args(int f);
int				init_args(t_infos *infos, char **av);
int				init_mutex(t_philo *philo, t_infos *infos);
void			*ft_routine(void *arg);
unsigned long	timestamp(void);
unsigned long	real_time(t_philo *philo);
int				ft_free_args(t_infos *infos, t_philo *philo, \
	pthread_mutex_t *mutex, int f);
void			death_checker(t_philo *philo, t_infos *infos);
void			dest_mutex(t_philo *philo);

#endif