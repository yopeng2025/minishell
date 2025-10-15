/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base2to16_lower_0x.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:04:38 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:45:32 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr_lower_0x(char *buffer, char *hex, uintptr_t nbr)
{
	int	i;
	int	count;

	i = 0;
	while (nbr > 0)
	{
		buffer[i] = hex[nbr % 16];
		i++;
		nbr /= 16;
	}
	count = i;
	i--;
	ft_putstr("0x");
	while (i >= 0)
	{
		ft_putchar(buffer[i]);
		i--;
	}
	return (count);
}

int	ft_base2to16_lower_0x(uintptr_t nbr)
{
	char	buffer[16];
	char	hex[16];
	int		count;

	ft_strcpy(hex, "0123456789abcdef");
	if (nbr == 0x0)
	{
		ft_putstr("0x0");
		return (3);
	}
	else
		count = ft_putaddr_lower_0x(buffer, hex, nbr);
	return (count + 2);
}
