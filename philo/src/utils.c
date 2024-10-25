/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:42:55 by eschmitz          #+#    #+#             */
/*   Updated: 2024/10/22 15:48:34 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *str, t_params *parameters, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (parameters->death)
			free(parameters->death);
		if (parameters->fork)
			free(parameters->fork);
		if (parameters->print_m)
			free(parameters->print_m);
		if (philo)
			free(philo);
	}
	return (printf("%s", str));
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	sign_space(char *str, int *ptr_len)
{
	int	sign;
	int	len;

	len = 0;
	sign = 1;
	while ((str[len] >= 9 && str[len] <= 13) || str[len] == 32)
		len++;
	if (str[len] && (str[len] == 43 || str[len] == 45))
	{
		if (str[len] == '-')
			sign *= -1;
		len++;
	}
	*ptr_len = len;
	return (sign);
}

long	ft_atoi(char *str)
{
	int					sign;
	unsigned long int	result;
	int					len;
	int					len_nb;

	result = 0;
	sign = sign_space(str, &len);
	len_nb = len;
	while (str[len] && str[len] == '0')
		len++;
	while (str[len] && str[len] >= 48 && str[len] <= 57)
	{
		result *= 10;
		result += str[len] - '0';
		len++;
		len_nb++;
		if (result > 2147483647 || result < 1)
		{
			printf("One arg is too big or = 0");
			return (-1);
		}
	}
	return ((long)result * sign);
}
