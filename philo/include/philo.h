/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:15:18 by fatilly           #+#    #+#             */
/*   Updated: 2022/03/22 14:10:18 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				eat;
	double			deadtime;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_thread	*t;
}				t_philo;

typedef struct s_thread
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				error;
	struct timeval	start;
	pthread_mutex_t	mutex;
	pthread_mutex_t	**fourchette;
	t_philo			**philo;
}				t_thread;

long				ft_atoi(const char *str);
int					print_error(char *s, t_thread *p);
void				print_etat(t_philo *p, char *s);
double				get_time(t_thread *p);
void				init_philo(t_thread *p);
t_thread			*init_thread(int i, int ac, char **av);
void				sleeping(t_philo *p);
void				thinking(t_philo *p);
void				*philosophers(void *philo);
int					is_alive(t_philo *p);
int					check_time(double time, t_thread *p);
int					isalldigit(char *s);

#endif