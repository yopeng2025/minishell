/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hexlower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:09:26 by peiyli            #+#    #+#             */
/*   Updated: 2025/07/04 16:52:40 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_hexlower(va_list args)
{
	int				count;
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	count = ft_base2to16_lower(nbr);
	return (count);
}
