/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:50:38 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 20:50:40 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *str, long long number, long long check)
{
	int	signcount;

	signcount = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signcount = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		check = (number * 10) + (*str - '0');
		if (check / 10 != number && signcount == 1)
			return (LLONG_MAX);
		if (check / 10 != number && signcount == -1)
			return (LLONG_MIN);
		number = check;
		str++;
	}
	return (number * signcount);
}
