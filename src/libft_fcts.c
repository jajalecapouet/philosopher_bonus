
#include "philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] == '\t') || (nptr[i] == '\n') || (nptr[i] == '\v')
		|| (nptr[i] == '\f') || (nptr[i] == '\r') || (nptr[i] == ' '))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		r = 10 * r;
		r = r + (nptr[i] - '0');
		i++;
	}
	return ((int)sign * r);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

void	ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*fill;

	i = 0;
	fill = s;
	while (i < n)
	{
		fill[i] = '\0';
		i++;
	}
}
