/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:12:25 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/22 15:49:14 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialise_thread(t_params *param, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < param->num_of_philos)
	{
		philo[i].right_fork = philo[(i + 1) % param->num_of_philos].left_fork;
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Error: Failed to create thread\n", param, philo, 1));
	}
	i = -1;
	param->start = get_time();
	while (++i < param->num_of_philos)
	{
		philo[i].thread_start = param->start;
		philo[i].meal = param->start;
	}
	param->ready = 1;
	return (0);
}

static void	free_thread(t_params *param, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < param->num_of_philos)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(param->death);
	pthread_mutex_destroy(param->fork);
	pthread_mutex_destroy(param->print_m);
	free(param->death);
	free(param->fork);
	free(param->print_m);
	free(philo);
}

static int	check_thread(t_params *param, t_philo *philo)
{
	int	i;

	while (!param->ready)
		continue ;
	while (!param->over)
	{
		i = -1;
		while (++i < param->num_of_philos)
			if (check_death(&philo[i]) || check_meals(i, philo[i]))
				param->over = 1;
	}
	if (param->check_meal && philo[param->num_of_philos - 1].iteration_number
		== param->maximum_iterations)
	{
		ft_usleep(5 * param->num_of_philos, philo);
		printf("\n  All philos have eaten %d times\n",
			philo->iteration_number);
		return (printf("No philosophers were harmed today\n\n"));
	}
	return (printf("\n   C'est Ciao Aladdin\n\n"));
}

static int	initialise_philo(t_params *param, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < param->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].iteration_number = 0;
		philo[i].meal = 0;
		philo[i].thread_start = 0;
		philo[i].parameters = param;
		philo[i].left_fork = &param->fork[i];
		philo[i].right_fork = 0;
	}
	return (0);
}

int	philosophers(t_params *parameters)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * parameters->num_of_philos);
	if (!philo)
		return (error_msg("Error\n", parameters, 0, 1));
	initialise_philo(parameters, philo);
	if (initialise_thread(parameters, philo))
		return (error_msg("Error\n", parameters, philo, 1));
	check_thread(parameters, philo);
	free_thread(parameters, philo);
	return (0);
}
