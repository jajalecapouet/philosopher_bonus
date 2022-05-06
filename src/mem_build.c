
#include "philo_bonus.h"

int	init_sem(t_law *law)
{
	int	fu_norminette;

	fu_norminette = law->philo_number;
	sem_unlink("/write");
	sem_unlink("/forks");
	sem_unlink("/remaining");
	sem_unlink("/die");
	law->die = sem_open("/die", O_CREAT, S_IRWXU, 1);
	law->write = sem_open("/write", O_CREAT, S_IRWXU, 1);
	law->remaining = sem_open("/remaining", O_CREAT, S_IRWXU, 0);
	law->forks = sem_open("/forks", O_CREAT, S_IRWXU, fu_norminette);
	return (0);
}

int	parsing(char **to_parse, t_law *to_fill)
{
	int	i;

	i = -1;
	while (to_parse[++i])
	{
		if (!ft_isdigit(to_parse[i][0]))
			return (22);
	}
	to_fill->philo_number = ft_atoi(to_parse[0]);
	to_fill->usleep_val = to_fill->philo_number * 25;
	to_fill->time_to_die = ft_atoi(to_parse[1]) * 1000;
	to_fill->time_to_eat = ft_atoi(to_parse[2]) * 1000;
	to_fill->time_to_sleep = ft_atoi(to_parse[3]) * 1000;
	to_fill->eat_number = -1;
	if (to_parse[4])
		to_fill->eat_number = ft_atoi(to_parse[4]);
	return (0);
}
