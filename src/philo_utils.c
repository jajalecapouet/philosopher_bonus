/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:11:25 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 18:37:44 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	je_mange(int n, t_time *tps, t_law *law)
{
	int			i;

	i = -1;
	while (++i < 2)
	{
		if (us(tps->last_eat, tps->current) >= law->time_to_die)
			return (1);
		sem_wait(law->forks);
		keskifou(law->write, tps, n, "has taken a fork\n");
	}
	gettimeofday(&tps->current, NULL);
	if (us(tps->last_eat, tps->current) >= law->time_to_die)
		return (1);
	keskifou(law->write, tps, n, "is eating\n");
	law->eat_number -= 1;
	gettimeofday(&tps->last_eat, NULL);
	usleep(law->time_to_eat);
	return (j_ai_fini(law, tps, n));
}

int	j_ai_fini(t_law *law, t_time *tps, int n)
{
	sem_post(law->forks);
	sem_post(law->forks);
	if (!law->eat_number)
		sem_post(law->remaining);
	gettimeofday(&tps->current, NULL);
	je_dors(n, tps, law);
	return (0);
}

void	je_dors(int n, t_time *tps, t_law *law)
{
	keskifou(law->write, tps, n, "is sleeping\n");
	if (law->time_to_die > law->time_to_eat + law->time_to_sleep)
		usleep(law->time_to_sleep);
	else
	{
		if (law->time_to_eat < law->time_to_die)
			usleep(law->time_to_die - law->time_to_eat);
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
		if (us(tps->last_eat, tps->current) > tps->law->time_to_die)
		{
			sem_wait(tps->law->die);
			keskifou(tps->law->write, tps, tps->n, "died\n");
			exit(0);
		}
		usleep(tps->law->usleep_val);
	}
	exit(0);
}

void	philo_handler(t_law law, int n)
{
	t_time		tps;
	int			think;
	pthread_t	timer_of_death;

	init_time(&tps, &law, n);
	think = 1;
	pthread_create(&timer_of_death, NULL, death_handler, &tps);
	while (1)
	{
		if (think)
			think = je_mange(n, &tps, &law);
		else
		{
			think = 1;
			keskifou(law.write, &tps, n, "is thinking\n");
		}
	}
	exit(0);
}
