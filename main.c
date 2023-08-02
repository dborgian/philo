/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:00:13 by dborgian          #+#    #+#             */
/*   Updated: 2023/08/02 15:12:57 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time / 10);
	return (0);
}

int	init_thread(t_data *data)
{
	int			i;
	pthread_t	monitor_thread_id;

	i = -1;
	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&monitor_thread_id, NULL,
				&monitoring, &data->philos[0]))
			return (printf("Error creating thread\n"));
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, & data->philos[i]))
			return (printf("Error creating thread\n"));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (printf("Error joining thread\n"));
	}
	return (0);
}

int	input_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (printf("Error: wrong input\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (printf("Error: pthread_create error\n"));
	pthread_detach(data->tid[0]);
	while (data->stop_eating == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
		return (1);
	if (input_check(argv))
		return (1);
	if (init(data, argv, argc))
		return (1);
	if (data->philo_num == 1)
		return (case_one(data));
	if (init_thread(data))
		return (1);
	ft_exit(data);
	return (0);
}
