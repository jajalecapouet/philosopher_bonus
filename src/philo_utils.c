
#include "philo_bonus.h"

void	philo_handler(law law, sem_t **semafork, char **fork_names, int n)
{
	if (semafork[0]->__sem_value == 0)
		exit (0);
}
