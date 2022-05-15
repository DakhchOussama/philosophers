/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:50:45 by odakhch           #+#    #+#             */
/*   Updated: 2022/05/12 19:18:09 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_semaphore(t_rules	*rules)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
	rules->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, rules->nb_philo);
	rules->writing = sem_open("/philo_write", O_CREAT, S_IRWXU, 1);
	rules->meal_check = sem_open("/philo_mealcheck", O_CREAT, S_IRWXU, 1);
	if (rules->forks <= 0 || rules->writing <= 0 || rules->meal_check <= 0)
		return (1);
	return (0);
}

int	modi_philo(t_rules	*rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->philosopher[i].id = i;
		rules->philosopher[i].x_ate = 0;
		rules->philosopher[i].last_meal = 0;
		rules->philosopher[i].rules = rules;
	}
	return (0);
}

int	init_all(t_rules	*rules, char	**argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->all_eat = 0;
	rules->dieded = 0;
	if (rules->nb_philo < 2 || rules->time_death < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0 || rules->nb_philo > 250)
		return (1);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	if (ft_semaphore(rules))
		return (1);
	modi_philo(rules);
	return (0);
}
