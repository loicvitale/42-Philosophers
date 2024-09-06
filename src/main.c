/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:37 by lvitale           #+#    #+#             */
/*   Updated: 2024/04/19 12:06:10 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_data(t_data *data, char **argv)
{
	int	i;
	int	temp;

	i = 0;
	while (argv[++i])
	{
		temp = ft_atoi(argv[i]);
		if (!temp || temp < 0)
			return (printf("Argument invalid\n"), 1);
	}
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_eat = -1;
	if (argv[5])
		data->number_of_eat = ft_atoi(argv[5]);
	data->starting_time = 0;
	pthread_mutex_init(&data->m_data, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_time, NULL);
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo)
		return (printf("malloc failed\n"), 1);
	i = -1;
	while (++i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].number_eat = 0;
		data->philo[i].is_dead = 0;
		pthread_mutex_init(&data->philo[i].fork, NULL);
	}
	return (0);
}

static void	clean_all(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->m_data);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_time);
	while (++i < data->number_of_philo)
		pthread_mutex_destroy(&data->philo[i].fork);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of arguments\n"), 1);
	if (init_data(&data, argv))
		return (1);
	if (init_philo(&data))
		return (1);
	start_sim(&data);
	clean_all(&data);
	return (0);
}
