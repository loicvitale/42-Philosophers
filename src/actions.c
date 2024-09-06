/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:59:32 by lvitale           #+#    #+#             */
/*   Updated: 2024/04/19 11:55:40 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(t_data *data, int index, char *str, int is_dead)
{
	pthread_mutex_lock(&data->m_print);
	if (!has_died(data))
	{
		printf("%d %d %s\n", get_time(data), index + 1, str);
		if (is_dead)
		{
			pthread_mutex_lock(&data->m_data);
			data->philo[index].is_dead = 1;
			pthread_mutex_unlock(&data->m_data);
		}
	}
	pthread_mutex_unlock(&data->m_print);
}

void	philo_take_fork(t_data *data, int index1, int index2)
{
	pthread_mutex_lock(&data->philo[index1].fork);
	print_message(data, index1, "has taken a fork", 0);
	pthread_mutex_lock(&data->philo[index2].fork);
	print_message(data, index1, "has taken a fork", 0);
}

void	philo_eating(t_data *data, int index1, int index2)
{
	print_message(data, index1, "is eating", 0);
	pthread_mutex_lock(&data->m_eat);
	data->philo[index1].last_eat = get_time(data);
	data->philo[index1].number_eat += 1;
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->philo[index2].fork);
	pthread_mutex_unlock(&data->philo[index1].fork);
}

void	philo_sleeping(t_data *data, int index)
{
	print_message(data, index, "is sleeping", 0);
	ft_sleep(data, data->time_to_sleep);
}
