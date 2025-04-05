/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/05 12:21:29 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_infos
{
	int	to_die;
	int num_philo;
	int	to_eat;
	int	to_sleep;
	int	must_eat;
}	t_infos;


typedef struct s_philo
{
	int id;
	long last_meal_time;
	pthread_t thread;
	pthread_mutex_t *forks;
	int someone_died;
	pthread_mutex_t *lfork;
	t_infos infos;
	pthread_mutex_t *rfork;
}	t_philo;

int		ft_atoi(char *s);
void	ft_putstr_fd(char *s, int fd);

#endif