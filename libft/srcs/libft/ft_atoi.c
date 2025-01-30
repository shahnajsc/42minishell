/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:30:23 by shachowd          #+#    #+#             */
/*   Updated: 2024/11/04 11:42:53 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atoi(const char *str)
{
	int		signcount;
	long	number;
	long	check;

	signcount = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signcount = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		check = (number * 10) + *str - 48;
		if (check / 10 != number && signcount == -1)
			return (0);
		if (check / 10 != number && signcount == 1)
			return (-1);
		number = check;
		str++;
	}
	return (number * signcount);
}
