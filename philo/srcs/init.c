/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:31:24 by fatilly           #+#    #+#             */
/*   Updated: 2022/04/12 15:12:50 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_thread	*init_fourchette(int i, t_thread *p)
{
	while (++i < p->num_of_phil)
	{
		p->fourchette[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(p->fourchette[i], NULL);
	}
	return (p);
}

t_thread	*init_thread(int i, int ac, char **av)
{
	t_thread	*p;

	p = malloc(sizeof(t_thread));
	gettimeofday(&p->start, NULL);
	p->error = 0;
	p->num_of_phil = ft_atoi(av[1]);
	p->philo = malloc(p->num_of_phil * sizeof(t_philo *));
	p->fourchette = malloc(p->num_of_phil * sizeof(pthread_mutex_t *));
	p = init_fourchette(-1, p);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac < 6)
		p->num_of_eat = -1;
	else
		p->num_of_eat = ft_atoi(av[5]);
	pthread_mutex_init(&p->mutex, NULL);
	while (av[++i])
		if (p->num_of_phil < 1 || !isalldigit(av[i]))
			p->error = 1;
	return (p);
}

void	init_philo(t_thread *p)
{
	int				i;

	i = -1;
	while (++i < p->num_of_phil)
	{
		p->philo[i] = malloc(sizeof(t_philo));
		p->philo[i]->id = i;
		p->philo[i]->eat = p->num_of_eat;
		p->philo[i]->t = p;
		p->philo[i]->deadtime = get_time(p) + p->time_to_die;
		pthread_mutex_init(&p->philo[i]->mutex, NULL);
		pthread_create(&p->philo[i]->thread, NULL, philosophers, &p->philo[i]);
		pthread_detach(p->philo[i]->thread);
		usleep(2000);
	}
}
