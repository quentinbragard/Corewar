/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 11:01:00 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 20:24:28 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char const *s, int fd)
{
	int i;

	if (s && !(i = 0))
	{
		while (s[i])
			i++;
		if (write(fd, s++, i) == -1)
			return ;
	}
}
