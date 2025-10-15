/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_unsignedint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:12:32 by peiyli            #+#    #+#             */
/*   Updated: 2025/07/04 16:53:26 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_unsignedint(va_list args)
{
	int				count;
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	ft_putnbr(nbr);
	count = ft_count_digit(nbr);
	return (count);
}
