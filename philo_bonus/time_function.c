/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:57:26 by odakhch           #+#    #+#             */
/*   Updated: 2022/05/07 16:57:28 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	div_time(long long past, long long present)
{
	return (present - past);
}

void	ft_sleep(long long time, t_rules *rules)
{
	long long	p;

	p = timestamp();
	while (!(rules->dieded))
	{
		if (div_time(p, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	write_act(t_rules *rules, int id, char *string)
{
	sem_wait(rules->writing);
	if (!(rules->dieded))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	sem_post(rules->writing);
	return ;
}

int	timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
