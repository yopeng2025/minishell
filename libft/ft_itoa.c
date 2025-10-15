/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:55:47 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:47:08 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_digit(long nbr)
{
	int	i;

	if (nbr == 0)
		return (1);
	i = 0;
	if (nbr < 0)
	{
		i++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		ndigit;
	long	nbr;
	char	*new;

	nbr = (long)n;
	ndigit = ft_nb_digit(nbr);
	new = (char *)malloc((ndigit + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[ndigit] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	while (ndigit > 0)
	{
		ndigit--;
		new[ndigit] = (nbr % 10) + '0';
		nbr = nbr / 10;
		if (ndigit == 1 && n < 0)
			break ;
	}
	if (n < 0)
		new[0] = '-';
	return (new);
}
