/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:19:47 by fatilly           #+#    #+#             */
/*   Updated: 2022/04/12 14:52:11 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_fourchettes(t_thread *p)
{
	int	i;

	i = -1;
	while (++i < p->num_of_phil)
		free(p->fourchette[i]);
	free(p->fourchette);
}

int	check_time(double time, t_thread *p)
{
	struct timeval	actual;

	gettimeofday(&actual, NULL);
	if (time >= get_time(p) - 5)
		return (1);
	return (0);
}

void	check_life(t_thread *p)
{
	int	i;
	int	j;

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < p->num_of_phil)
		{
			if (!p->philo[i]->eat)
				j++;
			if (j == p->num_of_phil)
				return ;
			if (!is_alive(p->philo[i]))
			{
				print_etat(p->philo[i], "died");
				pthread_mutex_lock(&p->mutex);
				return ;
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_thread	*p;
	int			i;

	if (ac < 5 || ac > 6)
		return (print_error("Incorrect number of arguments !", NULL));
	p = init_thread(0, ac, av);
	if (p->error)
		return (print_error("Invalid(s) parameter(s) !", p));
	init_philo(p);
	check_life(p);
	i = -1;
	while (++i < p->num_of_phil)
	{
		pthread_mutex_destroy(p->fourchette[i]);
		free(p->philo[i]);
	}
	pthread_mutex_destroy(&p->mutex);
	free_fourchettes(p);
	free(p->philo);
	free(p);
	return (0);
}
