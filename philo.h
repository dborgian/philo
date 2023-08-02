/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:23:33 by dborgian          #+#    #+#             */
/*   Updated: 2023/08/02 15:10:05 by dborgian         ###   ########.fr       */
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
# include <stdbool.h>

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

struct	s_data; 

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		superv;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	int				stop_eating;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

//general_utils
int			input_check(char **argv);
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strcmp(char *s1, char *s2);

//init
int			init_data(t_data *data, char **argv, int argc);
int			init_philos(t_data *data);
int			init_mutex(t_data *data);
int			init(t_data *data, char **argv, int argc);
int			alloc_data(t_data *data);
int			init_thread(t_data *data);
int			init_forks(t_data *data);

//routine
void		*routine(void *philo_pointer);
void		eating(t_philo *philo);
void		lock_forks(t_philo *philo);
void		unlock_forks(t_philo *philo);
void		prints(char *str, t_philo *philo);
void		*superv(void *philo_pointer);
int			ft_usleep(useconds_t time);
void		*monitoring(void *data_pointer);

//philo_utils
void		ft_exit(t_data *data);
void		clear_data(t_data *data);
u_int64_t	get_time(void);

#endif