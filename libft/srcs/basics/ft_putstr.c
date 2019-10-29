/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 23:08:13 by thzimmer          #+#    #+#             */
/*   Updated: 2018/11/09 20:34:18 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char const *s)
{
	int		i;

	if (s && !(i = 0))
	{
		while (s[i])
			i++;
		if (write(1, s, i) == -1)
			return ;
	}
}
