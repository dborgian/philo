/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:00:13 by dborgian          #+#    #+#             */
/*   Updated: 2023/07/26 16:58:02 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_check(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue;
			}
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (printf("Error: wrong input\n"));
			j++;
		}
		i++;
	}
	printf("Input is correct\n");
	return (0);
}


int main(int argc, char **argv)
{
	t_data data;

	if (argc < 5 || argc > 6)
		return (1);
	if (input_check(argv))
		return (1);
	if (init(&data, argv, argc))
		return (1);
	if (data.philo_num == 1)
		return (case_one(&data));
	if (thread_init(&data))
		return (1);
	ft_exit(&data);
	printf("Hello, world!\n");
	return (0);
}
