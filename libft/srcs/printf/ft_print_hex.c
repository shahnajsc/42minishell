/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:24:35 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/17 16:29:23 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(int fd, unsigned long nbr, char *strhex)
{
	int	p_len;

	p_len = 0;
	if (nbr >= 16)
	{
		p_len += ft_print_hex(fd, nbr / 16, strhex);
		if (p_len == -1)
			return (-1);
		p_len += ft_print_char(fd, strhex[nbr % 16]);
		if (p_len == -1)
			return (-1);
	}
	else
	{
		p_len += ft_print_char(fd, strhex[nbr]);
		if (p_len == -1)
			return (-1);
	}
	return (p_len);
}
