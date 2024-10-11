/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:17:13 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/11 10:31:38 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Locates the first occurrence of c in string.

#include "../pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s) + 1;
	while (len > 0)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
		len--;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
