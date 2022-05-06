
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
	struct law	law;
	int			err;

	if (ac < 5 || ac > 6)
		return(error(5));
	err = parsing(&av[1], &law);
	if (err)
		return (error(err));
	return (error(philo_bonus(law)));
}

int	philo_bonus(law law)
{
	sem_t	**semafork;
	char	**fork_names;

	i = -1;
	fork_names = init_fork_names(law.philo_number);
	if (!fork_names)
		return (11);
	semafork = init_semaphork(law.philo_number, fork_names);
	if (!semafork)
		return (freestyle(fork_name, 11));
	return (lets_fork_the_phils(fork_names, semafork, law));
}

int	lets_fork_the_phils(char **fork_names, sem_t **semafork, law law)
{
	pid_t	pid[law.philo_number];
	int		i;
	int		ret;

	i = -1;
	while (++i < law.philo_number)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			philo_handler(law, semafork, fork_names, i);
	}
	while (--i >= 0)
	{
		waitpid(-1, &ret, NULL);
		if (WEXISTATUS(ret))
		{
			kill(0, SIGINT);
			return (0);
		}
	}
	return (0);
}