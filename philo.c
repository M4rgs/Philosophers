/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:07:46 by tamounir          #+#    #+#             */
/*   Updated: 2025/03/31 12:12:38 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
volatile int someone_died = 0;  // Shared flag

/*void eat(Philosopher *philo) {
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % NUM_PHILOSOPHERS;

    // Try to pick up forks (avoid deadlock by always picking lower first)
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
    } else {
        pthread_mutex_lock(&forks[right_fork]);
        pthread_mutex_lock(&forks[left_fork]);
    }

    printf("Philosopher %d is eating...\n", philo->id);
    philo->last_meal_time = get_time_ms();
    sleep(TIME_TO_EAT);

    // Release forks
    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);
}*/
void	thinking(t_philo *philo)
{
	printf("Philo Number : %d is thinking\n", philo->id);
	usleep(500000);
}

long get_time_ms() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void	*ft_func(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	philo->last_meal_time = get_time_ms();
	while (!someone_died)
	{
		 long current_time = get_time_ms();
		if (current_time - philo->last_meal_time > philo->infos.to_die * 1000)
		{
			printf("philo Number : %d is dead lol\n", philo->id);
			someone_died = 1;
			return (NULL);
		}
		thinking (philo);
		printf("philo Number : %d is sleeping\n", philo->id);
		sleep(philo->infos.to_sleep);
	}
	return (NULL);
	
}

void	init_args(t_infos *infos, char **av)
{
	infos->num_philo = ft_atoi(av[1]);
	infos->to_die = ft_atoi(av[2]);
	infos->to_eat = ft_atoi(av[3]);
	infos->to_sleep = ft_atoi(av[4]);
	if (av[5])
		infos->must_eat = ft_atoi(av[5]);
	else
		infos->must_eat = -1;
	
	if (infos->num_philo <= 0 || infos->to_die <= 0 || infos->to_eat <= 0
		|| infos->to_sleep <= 0)
	{
		ft_putstr_fd("Error: Args\n", 2);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_infos infos;
	pthread_mutex_t *forks;
	int i = 0;

	if (ac == 5 || ac == 6)
	{
		init_args(&infos, av);
		philo = malloc(infos.num_philo * sizeof(t_philo));
		forks = malloc(infos.num_philo * sizeof(pthread_mutex_t));
		while (i < infos.num_philo)
		{
			pthread_mutex_init(&forks[i], NULL);
			i++;
		}
		i = 0;
		while (i < infos.num_philo)
		{
			philo[i].id = i;
			philo[i].lfork = &forks[i];
			philo[i].rfork = &forks[(i + 1) % infos.num_philo];
			philo[i].infos = infos;
			pthread_create(&philo[i].thread, NULL, ft_func, &philo[i]);
			i++;
		}
		i = 0;
		while (i < infos.num_philo)
		{
			pthread_join(philo[i].thread, NULL);
			i++;
		}
		free(forks);
		free(philo);
	}
}
