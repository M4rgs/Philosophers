/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 07:52:25 by tamounir          #+#    #+#             */
/*   Updated: 2025/04/14 07:57:53 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_infos
{
	/* data */
}	t_infos;

typedef struct s_philo
{
	/* data */
}	t_philo;

int				ft_atoi(char *s);
void			ft_putstr_fd(char *s, int fd);
int				err_args(int f);

#endif