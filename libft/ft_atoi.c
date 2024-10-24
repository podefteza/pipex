/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:12:38 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/24 09:19:02 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Converts string to an integer.

#include "../pipex.h"

int	ft_atoi(const char *nptr)
{
	int	digit;
	int	signal;

	digit = 0;
	signal = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = signal * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = (digit * 10) + (*nptr - '0');
		nptr++;
	}
	return (digit * signal);
}
