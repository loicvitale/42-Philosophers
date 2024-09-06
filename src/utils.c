/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:57:36 by lvitale           #+#    #+#             */
/*   Updated: 2024/04/19 12:13:11 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	unsigned long	nbr;
	int				sign;

	sign = 1;
	nbr = 0;
	while ((*str != '\0') && ((*str == 32) || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == 45)
	{
		sign *= -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while ((*str != '\0') && (*str >= 48 && *str <= 57))
	{
		nbr = (nbr * 10) + (*str - 48);
		str++;
		if ((nbr > LONG_MAX) && (sign == 1))
			return (-1);
		else if ((nbr > LONG_MAX) && (sign == -1))
			return (0);
	}
	return (nbr * sign);
}

void	ft_sleep(t_data *data, int time)
{
	int	start;

	start = get_time(data);
	while (get_time(data) < start + time)
		usleep(100);
}

int	has_died(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->m_data);
	while (++i < (int) data->number_of_philo)
		if (data->philo[i].is_dead == 1)
			return (pthread_mutex_unlock(&data->m_data), 1);
	return (pthread_mutex_unlock(&data->m_data), 0);
}

int	get_time(t_data *data)
{
	int				result;
	struct timeval	time;
	struct timeval	start;

	pthread_mutex_lock(&data->m_time);
	if (!data->starting_time)
	{
		gettimeofday(&start, NULL);
		data->starting_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->starting_time;
	pthread_mutex_unlock(&data->m_time);
	return (result);
}

t_table	*get_table(t_data *data)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table) * data->number_of_philo);
	if (!table)
		return (printf("malloc failed\n"), NULL);
	i = -1;
	while (++i < (int) data->number_of_philo)
	{
		table[i].data = data;
		table[i].index = i;
	}
	return (table);
}
