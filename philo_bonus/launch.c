/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:50:55 by odakhch           #+#    #+#             */
/*   Updated: 2022/05/07 16:54:55 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_exit(t_rules *rules)
{
	int		i;
	int		ret;

	i = 0;
	while (i < rules->nb_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < rules->nb_philo)
				kill(rules->philosopher[i].child_id, 15);
			break ;
		}
		i++;
	}
	sem_close(rules->forks);
	sem_close(rules->writing);
	sem_close(rules->meal_check);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
}

void	ft_process(void *void_philo)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	philo->last_meal = timestamp();
	pthread_create(&(philo->thread_id), NULL, check_death, void_philo);
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		philo_eat(philo);
		if (philo->x_ate >= rules->nb_eat && rules->nb_eat != -1)
			break ;
		write_act(rules, philo->id, "is sleeping");
		ft_sleep(rules->time_sleep, rules);
		write_act(rules, philo->id, "is thinking");
	}
	pthread_join(philo->thread_id, NULL);
	if (rules->dieded)
		exit(1);
	exit(0);
}

void	philo_eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	write_act(rules, philo->id, "has taken a fork");
	sem_wait(rules->forks);
	write_act(rules, philo->id, "has taken a fork");
	sem_wait(rules->meal_check);
	write_act(rules, philo->id, "is eating");
	philo->last_meal = timestamp();
	sem_post(rules->meal_check);
	ft_sleep(rules->time_eat, rules);
	(philo->x_ate)++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	*check_death(void *void_philo)
{
	int		i;
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->rules;
	i = -1;
	while (++i < rules->nb_philo && !(rules->dieded))
	{
		sem_wait(rules->meal_check);
		if (div_time(philo->last_meal, timestamp()) > rules->time_death)
		{
			write_act(rules, i, "died");
			rules->dieded = 1;
			sem_wait(rules->meal_check);
			exit(1);
		}
		sem_post(rules->meal_check);
		if (rules->dieded)
			break ;
		usleep(100);
		if (philo->x_ate >= rules->nb_eat && rules->nb_eat != -1)
			break ;
	}
	return (NULL);
}

int	launch(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = rules->philosopher;
	rules->first_timestamp = timestamp();
	while (++i < rules->nb_philo)
	{
		philo[i].child_id = fork();
		if (philo[i].child_id < 0)
			return (1);
		if (philo[i].child_id == 0)
			ft_process(&philo[i]);
		usleep(100);
	}
	launch_exit(rules);
	return (0);
}
