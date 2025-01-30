/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:36:40 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/17 16:36:11 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_format(int fd, va_list args, const char format)
{
	if (format == 'c')
		return (ft_print_char(fd, va_arg(args, int)));
	else if (format == 's')
		return (ft_print_str(fd, va_arg(args, char *)));
	else if (format == 'p')
		return (ft_print_ptr(fd, va_arg(args, unsigned long)));
	else if (format == 'd' || format == 'i')
		return (ft_print_nbr(fd, va_arg(args, int)));
	else if (format == 'u')
		return (ft_print_unsign(fd, va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_print_hex(fd, va_arg(args, unsigned int), HEX_LOWER));
	else if (format == 'X')
		return (ft_print_hex(fd, va_arg(args, unsigned int), HEX_UPPER));
	else if (format == '%')
		return (ft_print_percent(fd));
	else
		return (-1);
}

int	ft_printf(int fd, const char *str, ...)
{
	int			p_len;
	va_list		args;
	int			temp_len;

	p_len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && ft_strchr_pf("cspdiuxX%", *(str + 1)))
			temp_len = ft_check_format(fd, args, (*(++str)));
		else
			temp_len = ft_print_char(fd, *str);
		if (temp_len == -1)
			return (-1);
		p_len += temp_len;
		str++;
	}
	va_end(args);
	return (p_len);
}
