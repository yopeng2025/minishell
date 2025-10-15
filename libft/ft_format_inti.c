/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_inti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:26:05 by peiyli            #+#    #+#             */
/*   Updated: 2025/07/04 16:53:05 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_inti(va_list args)
{
	int	count;
	int	nbr;

	nbr = va_arg(args, int);
	ft_putnbr(nbr);
	count = ft_count_digit(nbr);
	return (count);
}
