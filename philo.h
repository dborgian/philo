/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:23:33 by dborgian          #+#    #+#             */
/*   Updated: 2023/07/26 17:09:08 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <time.h>
# include <stdbool.h>

struct	s_data; 

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t       superv;
	int             id;
	int             eat_cont;
	int             status;
	int             eating;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	pthread_t       *tid;
	int             philo_num;
	int             meals_nb;
	int             dead;
	int             finished;
	t_philo         *philos;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
} t_data;




int	input_check(char **argv);

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

//init

int	init_data(t_data *data, char **argv);
int	init_philos(t_data *data);
int	init_mutex(t_data *data);
int	init(t_data *data, char **argv, int argc);
int	alloc_data(t_data *data);

#endif