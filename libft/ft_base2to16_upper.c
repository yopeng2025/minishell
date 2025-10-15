/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base2to16_upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:44 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:45:36 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr_upper(char *buffer, uintptr_t nbr)
{
	int		i;
	int		count;
	char	hex[16];

	ft_strcpy(hex, "0123456789ABCDEF");
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

int	ft_base2to16_upper(unsigned int nbr)
{
	char		*buffer;
	int			count;
	int			i;
	uintptr_t	n;

	if (nbr == 0)
	{
		ft_putchar('0');
		return (1);
	}
	i = 0;
	n = nbr;
	while (n > 0)
	{
		i++;
		n = n / 16;
	}
	buffer = (char *)ft_calloc(i, sizeof(char));
	if (!buffer)
		return (0);
	count = ft_putaddr_upper(buffer, nbr);
	free(buffer);
	return (count);
}
