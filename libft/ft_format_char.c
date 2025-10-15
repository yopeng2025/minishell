/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:51:07 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:45:58 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_char(va_list args)
{
	int		count;
	char	ch;

	ch = va_arg(args, int);
	ft_putchar(ch);
	count = 1;
	return (count);
}
