/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:12:56 by eschmitz          #+#    #+#             */
/*   Updated: 2024/09/19 17:30:02 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialise_params_mutex(t_params *param)
{
	int	i;

	i = -1;
	param->death = 0;
	param->fork = 0;
	param->print_m = 0;
	param->death = malloc(sizeof(pthread_mutex_t));
	if (!param->death)
		return (error_msg("Error: Mutex death malloc failed\n", param, 0, 1));
	param->fork = malloc(sizeof(pthread_mutex_t) * param->num_of_philos);
	if (!param->fork)
		return (error_msg("Error: Mutex fork malloc failed\n", param, 0, 1));
	param->print_m = malloc(sizeof(pthread_mutex_t));
	if (!param->print_m)
		return (error_msg("Error: Mutex print_m malloc failed\n", param, 0, 1));
	if (pthread_mutex_init(param->death, NULL) == -1)
		return (error_msg("Error: Mutex init failed\n", param, 0, 1));
	if (pthread_mutex_init(param->print_m, NULL) == -1)
		return (error_msg("Error: Mutex init failed\n", param, 0, 1));
	while (++i < param->num_of_philos)
		if (pthread_mutex_init(&param->fork[i], NULL) == -1)
			return (error_msg("Error: Mutex init failed\n", param, 0, 1));
	return (0);
}

static int	initialise_params(t_params *param, char **argv)
{
	int	mutex;

	mutex = -1;
	param->num_of_philos = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	param->maximum_iterations = -2;
	param->check_meal = 0;
	param->start = 0;
	param->ready = 0;
	if (argv[5])
	{
		param->check_meal = 1;
		param->maximum_iterations = ft_atoi(argv[5]);
	}
	param->over = 0;
	if (param->num_of_philos > 0)
		mutex = initialise_params_mutex(param);
	return (mutex || param->num_of_philos <= 0
		|| param->time_to_die <= 0
		|| param->time_to_eat <= 0 || param->time_to_sleep <= 0
		|| param->maximum_iterations == 0);
}

int	main(int argc, char **argv)
{
	t_params	param;
	int			i;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]))
			return (printf("Error: Invalid arguments\n"), 1);
		i++;
	}
	if ((argc != 5 && argc != 6) || initialise_params(&param, argv))
		return (printf("Error: Invalid arguments\n"), 1);
	if (philosophers(&param))
		return (1);
	return (0);
}
