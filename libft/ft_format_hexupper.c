/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hexupper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:49:44 by peiyli            #+#    #+#             */
/*   Updated: 2025/07/04 16:52:46 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_hexupper(va_list args)
{
	int				count;
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	count = ft_base2to16_upper(nbr);
	return (count);
}
