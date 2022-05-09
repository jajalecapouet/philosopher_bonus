/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:11:25 by njaros            #+#    #+#             */
/*   Updated: 2022/05/09 09:56:49 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	je_mange(int n, t_time *tps, t_data *data)
{
	int			i;

	i = -1;
	while (++i < 2)
	{
		if (us(tps->last_eat, tps->current) >= data->time_to_die)
			return (1);
		sem_wait(data->forks);
		keskifou(data->write, tps, n, "has taken a fork\n");
	}
	if (us(tps->last_eat, tps->current) >= data->time_to_die)
		return (1);
	keskifou(data->write, tps, n, "is eating\n");
	data->eat_number -= 1;
	gettimeofday(&tps->last_eat, NULL);
	usleep(data->time_to_eat);
	return (j_ai_fini(data, tps, n));
}

int	j_ai_fini(t_data *data, t_time *tps, int n)
{
	sem_post(data->forks);
	sem_post(data->forks);
	if (!data->eat_number)
		sem_post(data->remaining);
	je_dors(n, tps, data);
	return (0);
}

void	je_dors(int n, t_time *tps, t_data *data)
{
	keskifou(data->write, tps, n, "is sleeping\n");
	if (data->time_to_die > data->time_to_eat + data->time_to_sleep)
		usleep(data->time_to_sleep);
	else
	{
		if (data->time_to_eat < data->time_to_die)
			usleep(data->time_to_die - data->time_to_eat);
	}
}

void	*death_handler(void *arg)
{
	t_time	*tps;
	sem_t	*die;

	tps = arg;
	die = sem_open("/die", 0);
	while (1)
	{
		gettimeofday(&tps->current, NULL);
		if (us(tps->last_eat, tps->current) > tps->data->time_to_die)
		{
			sem_wait(tps->data->die);
			keskifou(tps->data->write, tps, tps->n, "died\n");
			sem_close(die);
			exit(0);
		}
		usleep(tps->data->usleep_val);
	}
	exit(0);
}

void	philo_handler(t_data data, int n)
{
	t_time		tps;
	int			think;
	pthread_t	timer_of_death;

	init_time(&tps, &data, n);
	think = 1;
	if (pthread_create(&timer_of_death, NULL, death_handler, &tps))
	{
		write(2, "la création du thread d'un fork à échoué\n", 46);
		exit(0);
	}
	while (1)
	{
		if (think)
			think = je_mange(n, &tps, &data);
		else
		{
			think = 1;
			keskifou(data.write, &tps, n, "is thinking\n");
		}
	}
}
