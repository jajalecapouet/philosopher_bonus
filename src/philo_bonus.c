/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:40:11 by njaros            #+#    #+#             */
/*   Updated: 2022/05/06 17:43:09 by njaros           ###   ########lyon.fr   */
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
		return(error(5));
	err = parsing(&av[1], &law);
	if (err)
		return (error(err));
	err = init_sem(&law);
	if (err)
		return (error(err));
	if (!law.philo_number || !law.eat_number)
		return (0);
	return (error(philo_bonus(law)));
}

void	*meal_counter_handler(void *arg)
{
	t_law	*law;
	int		count;

	law = arg;
	count = law->philo_number;
	while (--count >= 0)
		sem_wait(law->remaining);
	kill(0, SIGINT);
	return (NULL);
}

int	philo_bonus(t_law law)
{
	pthread_t	meal_counter;

	pthread_create(&meal_counter, NULL, meal_counter_handler, &law);
	return (lets_fork_the_phils(law));
}

int	lets_fork_the_phils(t_law law)
{
	pid_t	pid[law.philo_number];
	int		i;
	int		ret;

	i = -1;
	gettimeofday(&law.start, NULL);
	while (++i < law.philo_number)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			philo_handler(law, i);
	}
	waitpid(-1, &ret, 0);
	kill(0, SIGINT);
	return (0);
}
