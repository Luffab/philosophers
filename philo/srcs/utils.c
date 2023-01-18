/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:17:57 by fatilly           #+#    #+#             */
/*   Updated: 2022/03/22 14:06:09 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *s, t_thread *p)
{
	int		i;

	printf("%s\n", s);
	if (!p)
		return (1);
	i = -1;
	while (++i < p->num_of_phil)
		pthread_mutex_destroy(p->fourchette[i]);
	pthread_mutex_destroy(&p->mutex);
	free(p->fourchette);
	free(p->philo);
	free(p);
	return (1);
}

long	ft_atoi(const char *str)
{
	int		start;
	int		i;
	long	res;
	int		negative;

	start = 0;
	while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t'
			|| str[start] == '\r' || str[start] == '\n'))
		start++;
	i = start;
	res = 0;
	negative = 0;
	while (str[i] != '\0' && ((str[i] >= '0' && str[i] <= '9')
			|| (i == start && (str[i] == '-' || str[i] == '+'))))
	{
		if (str[i] == '-')
			negative = 1;
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i] - 48);
		++i;
	}
	if (negative)
		res *= -1;
	return (res);
}

void	print_etat(t_philo *p, char *s)
{
	struct timeval	actual;
	double			time;

	pthread_mutex_lock(&p->t->mutex);
	gettimeofday(&actual, NULL);
	time = (double)(actual.tv_usec - p->t->start.tv_usec) / 1000 + (double)
		(actual.tv_sec - p->t->start.tv_sec) * 1000;
	printf("%.f %d %s\n", time, p->id + 1, s);
	pthread_mutex_unlock(&p->t->mutex);
}

double	get_time(t_thread *p)
{
	struct timeval	actual;

	gettimeofday(&actual, NULL);
	return ((double)(actual.tv_usec - p->start.tv_usec) / 1000 +
	(double)(actual.tv_sec - p->start.tv_sec) * 1000);
}
