
#include "philo_bonus.h"

int	parsing(char **to_parse, law *to_fill)
{
	int	i;

	i = -1;
	while (to_parse[++i])
	{
		if (!ft_isdigit(to_parse[i][0]))
			return (22);
	}
	to_fill->philo_number = ft_atoi(to_parse[0]);
	to_fill->time_to_die = ft_atoi(to_parse[1]) * 1000;
	to_fill->time_to_eat = ft_atoi(to_parse[2]) * 1000;
	to_fill->time_to_sleep = ft_atoi(to_parse[3]) * 1000;
	to_fill->eat_number = 0;
	if (to_parse[4])
		to_fill->eat_number += ft_atoi(to_parse[4]);
	return (0);
}

char	*crea_name(int nb)
{
	char	*name;
	char	*itoa_nb;
	int		size;

	itoa_nb = ft_itoa(nb);
	if (!itoa_nb)
		return (NULL);
	size = ft_strlen(itoa_nb) + 2;
	name = malloc(size);
	if (!name)
	{
		free(itoa_nb);
		return (NULL);
	}
	ft_bzero(name, size);
	ft_strcat(name, "/");
	ft_strcat(name, itoa_nb);
	free(itoa_nb);
	return (name);
}

char	**init_fork_names(int size)
{
	int		i;
	char	**names;

	i = -1;
	names = malloc(sizeof(char *) * size + 2);
	if (!names)
		return (NULL);
	names[size + 1] = NULL;
	while (++i < size + 1)
	{
		if (i == 0)
			name[i] = ft_strdup("/remaining");
		else
			names[i] = crea_name(i);
		if (!names[i])
		{
			while (--i >= 0)
				free(names[i]);
			free(names);
			return (NULL);
		}
	}
	return (names);
}

sem_t	**init_semafork(int size, char **names)
{
	int		i;
	sem_t	**semafork;

	i = -1;
	semafork = malloc(sizeof(sem_t *) * size + 2);
	semafork[size + 1] = NULL;
	while (++i < size + 1)
	{
		if (i == 0)
			semafork[i] = sem_open(names[i], O_CREAT, 0x1B6, size);
		else
			semafork[i] = sem_open(names[i], O_CREAT, 0x1B6, 1);
		if (semafork[i] == SEM_FAILED)
		{
			while (--i <= 0)
			{
				sem_close(semafork[i]);
				sem_unlink(names[i]);
			}
			return (NULL);
		}
	}
	return (semafork);
}
