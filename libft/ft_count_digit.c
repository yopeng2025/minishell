/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:16:37 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:45:55 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digit(long long nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb / 10 >= 1)
	{
		count++;
		nb /= 10;
	}
	return (count);
}
