/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:59:51 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:50:59 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	src_size = 0;
	while (src[src_size])
		src_size++;
	dst_size = 0;
	while (dst_size < dstsize && dst[dst_size])
		dst_size++;
	if (dst_size == dstsize)
		return (dstsize + src_size);
	i = 0;
	while ((dst_size + i) < (dstsize - 1) && src[i])
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + src_size);
}
