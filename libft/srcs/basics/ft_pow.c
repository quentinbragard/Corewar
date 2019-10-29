/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 11:28:19 by thzimmer          #+#    #+#             */
/*   Updated: 2018/11/10 18:10:50 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_pow(int nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (nb * ft_pow(nb, power - 1));
}
