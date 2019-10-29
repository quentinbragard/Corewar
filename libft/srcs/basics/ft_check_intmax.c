/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_intmax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:50:38 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 18:50:41 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_atoi(char const *str)
{
	int					i;
	int					neg;
	unsigned long long	result;

	i = 0;
	neg = 1;
	result = 0;
	while (*str == ' ' || (*str > '\a' && *str <= '\r'))
		str++;
	if ((*str == '-' && (neg = -1)) || *str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (result * neg);
}

/*
** Checks for maximum integer range and return its length on success.
*/

char		ft_check_intmax(char *str)
{
	int len;

	len = 0;
	while (str[len] >= '0' && str[len] <= '9')
		len++;
	if (!len || len > 10 || (len == 10 && *str == '2'
					&& ft_atoi(str + 1) > 147483647))
		return (0);
	return (1);
}
