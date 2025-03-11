/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/03/11 15:29:52 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>

typedef struct s_time
{
	int	to_die;
	int	to_eat;
	int	to_sleep;
	int	must_eat;
}	t_time;

typedef struct s_philo
{
	int		philos;
	void	*mutex;
	t_time	time;
}	t_philo;

int		ft_atoi(char *s);
void	ft_putstr_fd(char *s, int fd);

#endif