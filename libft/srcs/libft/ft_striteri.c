/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:36:30 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/16 16:27:17 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char			*str;
	unsigned int	count;

	str = (char *)s;
	if (str && f)
	{
		count = 0;
		while (str[count])
		{
			(*f)(count, &str[count]);
			count++;
		}
	}
}
/*	-Usees external function 'f' as argument to iterate string 's'.
	-Applies 'f' on each character of 's' passed as 
		argument (index & character).
	-Each character is passed by address to 'f', to be
		modified if necessary. 
	-External function: none.
	-Return: None.
*/