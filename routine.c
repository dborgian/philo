/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:57:46 by dborgian          #+#    #+#             */
/*   Updated: 2023/07/26 17:20:04 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*routine(void *philo_pointer)
{
	t_philo	*philo;
	philo = (t_philo *)philo_pointer;
	
	philo = time->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&data->superv, NULL, &superv, (void *)philo))
		return ((void *)1);
	while(philo->data->dead == 0)
	{
		eating(philo);
		prints(THINKING, philo);
	}
	if (pthread_join(data->superv, NULL))
		return ((void *)1);
	return ((void *)0);
}




u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday FAILURE\n"));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (printf("Error: pthread_create error\n"));
	
}