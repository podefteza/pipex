/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:56:59 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/08 12:22:52 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strlcpy() function copies up to size - 1 characters from the
NUL-terminated string src to dst, NUL-terminating the result. */

#include "../pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
