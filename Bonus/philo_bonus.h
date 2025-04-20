/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 07:52:25 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/20 17:42:54 by tamounir         ###   ########.fr       */
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
void			init_data(t_infos *infos);
size_t			timing(void);

#endif