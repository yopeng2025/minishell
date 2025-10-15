/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hexvoid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:04:49 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:46:17 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_hexvoid(va_list args)
{
	int			count;
	uintptr_t	address;

	address = va_arg(args, uintptr_t);
	if (!address)
	{
		ft_putstr("(nil)");
		return (5);
	}
	count = ft_base2to16_lower_0x(address);
	return (count);
}
