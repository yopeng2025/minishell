/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:16:31 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:46:26 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(const char *c, va_list args)
{
	int		count;

	count = 0;
	if (*c == 'c')
		count = ft_format_char(args);
	else if (*c == 's')
		count = ft_format_str(args);
	else if (*c == 'p')
		count = ft_format_hexvoid(args);
	else if (*c == 'd' || *c == 'i')
		count = ft_format_intd(args);
	else if (*c == 'u')
		count = ft_format_unsignedint(args);
	else if (*c == 'x')
		count = ft_format_hexlower(args);
	else if (*c == 'X')
		count = ft_format_hexupper(args);
	else if (*c == '%')
		count = ft_format_percent('%');
	return (count);
}
