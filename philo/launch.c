/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:23:58 by odakhch           #+#    #+#             */
/*   Updated: 2022/04/25 17:27:34 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_exit(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}

void	*ft_thread(void *void_philo)
{
	int		i;
	t_philo	*philo;
	t_rules	*rules;

	i = 0;
	philo = (t_philo *)void_philo;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		philo_eat(philo);
		if (rules->all_eat)
			break ;
		write_act(rules, philo->id, "is sleeping");
		ft_sleep(rules->time_sleep, rules);
		write_act(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	write_act(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork]));
	write_act(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	write_act(rules, philo->id, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	ft_sleep(rules->time_eat, rules);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork]));
}

void	check_death(t_rules *rules, t_philo *philo)
{
	int	i;

	while (!(rules->all_eat))
	{
		i = -1;
		while (++i < rules->nb_philo && !(rules->dieded))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if (div_time(philo[i].last_meal, timestamp()) > rules->time_death)
			{
				write_act(rules, i, "died");
				rules->dieded = 1;
			}
			pthread_mutex_unlock(&(rules->meal_check));
			usleep(100);
		}
		if (rules->dieded)
			break ;
		i = 0;
		while (rules->nb_eat != -1 && i < rules->nb_philo
			&& philo[i].x_ate >= rules->nb_eat)
			i++;
		if (i == rules->nb_philo)
			rules->all_eat = 1;
	}
}

int	launch(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philosopher;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, ft_thread, &(philo[i])))
			return (1);
		philo[i].last_meal = timestamp();
		i++;
	}
	check_death(rules, rules->philosopher);
	launch_exit(rules, philo);
	return (0);
}
