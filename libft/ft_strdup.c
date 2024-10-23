/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:22:12 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/18 14:12:40 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns a pointer to a null-terminated byte string, which is a duplicate of
the string pointed to by s. */

#include "../pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	int (size);
	int (i);
	size = ft_strlen(s) + 1;
	i = 0;
	dest = (char *)malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
