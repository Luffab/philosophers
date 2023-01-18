/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:32:45 by fatilly           #+#    #+#             */
/*   Updated: 2022/04/12 15:08:07 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *p)
{
	if (p->deadtime == -1)
		return (1);
	if (!check_time(p->deadtime, p->t))
		return (0);
	return (1);
}

void	sleeping(t_philo *p)
{
	pthread_mutex_lock(&(p->mutex));
	if (is_alive(p))
		print_etat(p, "is sleeping");
	usleep(p->t->time_to_sleep * 1000);
	pthread_mutex_unlock(&(p->mutex));
}

void	try_to_eat(t_philo *p)
{
	pthread_mutex_lock(&p->mutex);
	pthread_mutex_lock(p->t->fourchette[p->id]);
	print_etat(p, "has taken a fork");
	pthread_mutex_lock(p->t->fourchette[(p->id + 1) % p->t->num_of_phil]);
	print_etat(p, "has taken a fork");
	print_etat(p, "is eating");
	p->deadtime = get_time(p->t) + p->t->time_to_die;
	usleep(p->t->time_to_eat * 1000);
	p->eat -= 1;
	pthread_mutex_unlock(p->t->fourchette[p->id]);
	pthread_mutex_unlock(p->t->fourchette[(p->id + 1) % p->t->num_of_phil]);
	pthread_mutex_unlock(&(p->mutex));
}

void	*philosophers(void *philo)
{
	t_philo	**p;

	p = philo;
	while ((*p)->eat != 0)
	{
		print_etat(*p, "is thinking");
		try_to_eat(*p);
		dprintf(1, "[%d]\n", (*p)->eat);
		if ((*p)->eat)
			sleeping(*p);
	}
	(*p)->deadtime = -1;
	return (philo);
}
