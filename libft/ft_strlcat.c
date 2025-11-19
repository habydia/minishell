/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:56:38 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	size_dst;
	size_t	size_src;

	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	j = size_dst;
	i = 0;
	if (size_dst < n - 1 && n > 0)
	{
		while (src[i] && size_dst + i < n - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = '\0';
	}
	if (size_dst >= n)
		size_dst = n;
	return (size_dst + size_src);
}
