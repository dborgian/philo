/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:57:46 by dborgian          #+#    #+#             */
/*   Updated: 2023/08/02 15:14:57 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->superv, NULL, &superv, (void *)philo))
		return ((void *)1);
	while (philo->data->stop_eating == 0)
	{
		eating(philo);
		prints(THINKING, philo);
	}
	if (pthread_join(philo->superv, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	prints(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DEAD, str) == 0 && philo->data->stop_eating == 0)
	{
		printf("%lu %d %s\n", time, philo->id, str);
		philo->data->stop_eating = 1;
	}
	if (!philo->data->stop_eating)
		printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	eating(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = philo->data->death_time + get_time();
	prints(EATING, philo);
	philo->eat_cont++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	unlock_forks(philo);
}

void	*superv(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->stop_eating == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			prints(DEAD, philo);
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*monitoring(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	pthread_mutex_lock(&philo->data->write);
	printf("data value = %d\n", philo->data->stop_eating);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->stop_eating == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->stop_eating = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}
