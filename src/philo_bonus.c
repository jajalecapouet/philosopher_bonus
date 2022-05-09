/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:40:11 by njaros            #+#    #+#             */
/*   Updated: 2022/05/09 13:03:46 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error(int err)
{
	if (err == 1)
		write(2, "Opération non autorisée\n", 27);
	if (err == 3)
		write(2, "Aucun processus de ce type\n", 28);
	if (err == 5)
		write(2, "Erreur d'E/S\n", 13);
	if (err == 11 || err == 12)
		write(2, "Erreur mémoire\n", 16);
	if (err == 22)
		write(2, "Argument(s) non valide\n", 24);
	if (err == 36)
		write(2, "Un interblocage des ressources se produirait.\n", 47);
	return (err);
}

int	main(int ac, char **av)
{
	t_law		law;
	int			err;

	if (ac < 5 || ac > 6)
		return (error(5));
	err = parsing(&av[1], &law);
	if (err)
		return (error(err));
	err = init_sem(&law);
	if (err)
		return (error(err));
	if (!law.philo_number || !law.eat_number)
		return (0);
	err = philo_bonus(&law);
	gordon_freeman(&law);
	return (error(err));
}

void	*meal_counter_handler(void *arg)
{
	t_law	*law;
	int		count;
	int		to_int;

	to_int = -1;
	law = arg;
	count = law->philo_number;
	while (--count >= 0)
		sem_wait(law->remaining);
	while (++to_int < law->philo_number)
		kill(law->pid_adr[to_int], SIGINT);
	return (NULL);
}

int	philo_bonus(t_law *law)
{
	pthread_t	meal_counter;
	pid_t		*pid;
	int			err;

	pid = malloc(sizeof(int) * law->philo_number);
	if (!pid)
		return (12);
	law->pid_adr = pid;
	err = pthread_create(&meal_counter, NULL, meal_counter_handler, law);
	if (err)
		return (err);
	err = lets_fork_the_phils(law);
	if (err <= 0)
	{
		pthread_detach(meal_counter);
		while (++err <= 0)
			kill(pid[-err], SIGINT);
		return (12);
	}
	pthread_detach(meal_counter);
	return (0);
}

int	lets_fork_the_phils(t_law *law)
{
	int		i;
	int		ret;
	t_data	fork_data;

	i = -1;
	gettimeofday(&law->start, NULL);
	data_builder(&fork_data, law);
	while (++i < law->philo_number)
	{
		law->pid_adr[i] = fork();
		if (law->pid_adr[i] == -1)
			return (-i);
		if (law->pid_adr[i] == 0)
			philo_handler(fork_data, i);
	}
	waitpid(-1, &ret, 0);
	if (WIFEXITED(ret))
	{
		while (--i >= 0)
			kill(law->pid_adr[i], SIGINT);
	}
	return (1);
}
