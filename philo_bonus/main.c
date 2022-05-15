/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:51:04 by odakhch           #+#    #+#             */
/*   Updated: 2022/05/12 19:17:48 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (ft_error("At least one wrong argument"));
	if (error == 2)
		return (ft_error("Fatal error when intializing mutex"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		ret;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong arguments"));
	ret = init_all(&rules, argv);
	if (ret)
		return (error_manager(ret));
	if (launch(&rules))
		return (ft_error("ERROR in threads"));
	return (0);
}
