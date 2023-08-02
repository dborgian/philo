/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:28:46 by dborgian          #+#    #+#             */
/*   Updated: 2023/08/02 14:51:57 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

void	clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	prints(FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	prints(FORK, philo);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	prints(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday FAILURE\n"));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
