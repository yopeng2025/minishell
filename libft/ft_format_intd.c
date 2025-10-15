/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_intd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:19:08 by peiyli            #+#    #+#             */
/*   Updated: 2025/07/04 16:52:59 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_intd(va_list args)
{
	int		count;
	int		nbr;

	nbr = va_arg(args, int);
	ft_putnbr(nbr);
	count = ft_count_digit(nbr);
	return (count);
}
