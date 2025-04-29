/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 07:52:25 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/29 23:46:22 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <signal.h>

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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*last_meal;
	sem_t			*count;
	size_t			is_dead;
	pthread_t		thread;
	int				index;
	t_philo			*philo;
}	t_infos;

typedef struct s_philo
{
	int		id;
	size_t	ate;
	pid_t	proccess_id;
	size_t	last_time_eat;
	t_infos	*infos;
	sem_t	sema;
	pid_t	pid;
}	t_philo;

int				ft_atoi(char *s);
void			ft_putstr_fd(char *s, int fd);
int				err_args(int f);
int				init_args(t_infos *infos, char **av);
int				init_data(t_infos *infos);
int				proccess_init(t_infos *infos);
void			ft_routine(t_infos *infos, t_philo *philo);
size_t			timing(void);
int				ft_usleep(size_t ms);
void			*monitor(void *argss);
void			kill_and_close(t_infos *infos);

#endif