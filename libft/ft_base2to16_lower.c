/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base2to16_lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:02:40 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:45:41 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr_lower(char *buffer, char *hex, uintptr_t nbr)
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
	while (i >= 0)
	{
		ft_putchar(buffer[i]);
		i--;
	}
	return (count);
}

int	ft_base2to16_lower(unsigned int nbr)
{
	char	buffer[16];
	char	hex[16];
	int		count;

	ft_strcpy(hex, "0123456789abcdef");
	if (nbr == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
		count = ft_putaddr_lower(buffer, hex, nbr);
	return (count);
}
