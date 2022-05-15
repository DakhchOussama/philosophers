/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 02:25:11 by odakhch           #+#    #+#             */
/*   Updated: 2022/04/26 02:34:41 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct t_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				last_meal;
	int				x_ate;
	struct t_rules	*rules;
	pthread_t		thread_id;
}					t_philo;

typedef struct t_rules
{
	int				nb_philo;
	int				time_death;
	int				time_sleep;
	int				dieded;
	int				nb_eat;
	long long		first_timestamp;
	int				time_eat;
	int				all_eat;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	t_philo			philosopher[250];
}					t_rules;

int			ft_error(char *msg);
int			error_manager(int error);
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str);
long long	div_time(long long past, long long present);
void		ft_sleep(long long time, t_rules *rules);
int			timestamp(void);
void		write_act(t_rules *rules, int id, char *msg);
void		philo_eat(t_philo *philo);
void		*ft_thread(void *o_philo);
void		check_death(t_rules *rules, t_philo *philo);
void		launch_exit(t_rules *rules, t_philo *philo);
int			launch(t_rules *rules);
int			init_all(t_rules *rules, char **av);
int			ft_mutex(t_rules *rules);
int			modi_philo(t_rules *rules);

#endif
