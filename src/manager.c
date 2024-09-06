/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:59:23 by lvitale           #+#    #+#             */
/*   Updated: 2024/04/19 12:13:17 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	get_prev_index(t_data *data, int index)
{
	if (index == 0)
		return (data->number_of_philo - 1);
	return (index - 1);
}

static	void	*routine(void *args)
{
	t_table	*table;
	int		index1;
	int		index2;

	table = (t_table *)args;
	index1 = table->index;
	index2 = get_prev_index(table->data, index1);
	table->data->philo[index1].last_eat = get_time(table->data);
	if (table->data->philo[index1].id % 2 == 0)
		ft_sleep(table->data, table->data->time_to_eat / 10);
	while (!has_died(table->data))
	{
		if (table->data->number_of_philo != 1)
		{
			philo_take_fork(table->data, index1, index2);
			philo_eating(table->data, index1, index2);
			if (table->data->philo[index1].number_eat
				== table->data->number_of_eat)
				return (NULL);
		}
		philo_sleeping(table->data, index1);
		print_message(table->data, index1, "is thinking", 0);
	}
	return (NULL);
}

static int	max_eat(t_data *data)
{
	int	i;

	if (data->number_of_eat == -1)
		return (0);
	i = -1;
	while (++i < data->number_of_philo)
		if (data->philo[i].number_eat != data->number_of_eat)
			return (0);
	pthread_mutex_lock(&data->m_data);
	data->philo[0].is_dead = 1;
	pthread_mutex_unlock(&data->m_data);
	return (1);
}

static void	*philo_manager(void *args)
{
	t_data	*data;
	int		i;
	int		time;

	data = (t_data *)args;
	while (1)
	{
		i = -1;
		while (++i < data->number_of_philo)
		{
			time = get_time(data);
			pthread_mutex_lock(&data->m_eat);
			if (time - data->philo[i].last_eat >= data->time_to_die)
			{
				print_message(data, i, "died", 1);
				return (pthread_mutex_unlock(&data->m_eat), NULL);
			}
			pthread_mutex_unlock(&data->m_eat);
			if (max_eat(data))
				return (NULL);
		}
	}
	return (NULL);
}

int	start_sim(t_data *data)
{
	int			i;
	t_table		*table;
	pthread_t	temp;

	table = get_table(data);
	if (!table)
		return (1);
	i = -1;
	while (++i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&table[i]) != 0)
			return (free(table), printf("pthread_create failed\n"), 1);
	}
	if (pthread_create(&temp, NULL, &philo_manager, data) != 0)
		return (free(table), printf("pthread_create failed\n"), 1);
	i = -1;
	while (++i < data->number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(table), printf("pthread_join failed\n"), 1);
	if (pthread_join(temp, NULL) != 0)
		return (free(table), printf("pthread_join failed\n"), 1);
	return (0);
}
