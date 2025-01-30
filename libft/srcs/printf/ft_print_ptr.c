/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:24:33 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/17 16:28:28 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(int fd, unsigned long ptr)
{
	int	p_len;

	p_len = 0;
	if (ptr == 0)
	{
		p_len = ft_print_str(fd, PTR_NULL);
		if (p_len == -1)
			return (-1);
		return (p_len);
	}
	p_len += ft_print_str(fd, "0x");
	if (p_len == -1)
		return (-1);
	p_len += ft_print_hex(fd, ptr, HEX_LOWER);
	if (p_len == -1)
		return (-1);
	return (p_len);
}
