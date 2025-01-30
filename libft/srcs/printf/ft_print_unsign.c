/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:18:53 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/17 16:27:29 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsign(int fd, unsigned int nbr)
{
	int	p_len;

	p_len = 0;
	if (nbr >= 10)
	{
		p_len = ft_print_unsign(fd, nbr / 10);
		if (p_len == -1)
			return (-1);
		nbr = nbr % 10;
	}
	if (nbr <= 9)
	{
		if (ft_print_char(fd, (nbr + '0')) == -1)
			return (-1);
		p_len++;
	}
	return (p_len);
}
