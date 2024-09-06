/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:25:13 by lvitale           #+#    #+#             */
/*   Updated: 2024/04/19 12:13:04 by lvitale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				number_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				is_dead;
}	t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				starting_time;
	t_philo			*philo;
	pthread_mutex_t	m_data;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_time;
}		t_data;

typedef struct s_table
{
	t_data			*data;
	int				index;
}					t_table;

/* utils.c */
int		ft_atoi(char *str);
void	ft_sleep(t_data *data, int time);
int		has_died(t_data *data);
int		get_time(t_data *data);
t_table	*get_table(t_data *data);

/* manager.c */
int		start_sim(t_data *data);

/* actions.c */
void	print_message(t_data *data, int index, char *str, int is_dead);
void	philo_take_fork(t_data *data, int index1, int index2);
void	philo_eating(t_data *data, int index1, int index2);
void	philo_sleeping(t_data *data, int index);

#endif