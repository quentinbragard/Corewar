/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_short_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:04:01 by thzimmer          #+#    #+#             */
/*   Updated: 2019/09/10 15:04:18 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Swap bytes for BIG_ENDIAN notation (2 bytes)
*/

int			get_short(unsigned char *arena, int index)
{
	return ((int)((short)((arena[index] & 0xff) << 8 \
		| (arena[MODM(index + 1)] & 0xff))));
}

/*
** Swap bytes for BIG_ENDIAN notation (4 bytes)
*/

int			get_int(unsigned char *arena, int index)
{
	return ((int)((arena[index] & 0xff) << 24 \
		| (arena[MODM(index + 1)] & 0xff) << 16 \
		| (arena[MODM(index + 2)] & 0xff) << 8 \
		| (arena[MODM(index + 3)] & 0xff)));
}

/*
** Writes val as 4 bytes on the map.
*/

void		write_arena(unsigned char *arena, int index, int val)
{
	unsigned char	*ptr;
	int				reversed;
	int				i;

	reversed = get_int((unsigned char *)&val, 0);
	ptr = (unsigned char *)&reversed;
	i = -1;
	while (++i < 4)
	{
		arena[MODM(index)] = ptr[i];
		index++;
	}
}

/*
** Print the arena.
*/

void		print_map(t_game *game)
{
	int	i;

	i = -1;
	ft_printf("Dump at cycle [%d] :\n", game->dump);
	ft_printf("\033[30;1m0x0000.\033[0m ");
	while (++i < MEM_SIZE)
	{
		if (i && !(i % 64))
			ft_printf("\n\033[30;1m%#06x.\033[0m ", i);
		if (game->viewer.color[i] == 0)
			write(1, BLACK, 7);
		else if (game->viewer.color[i] == 1)
			write(1, GREEN, 5);
		else if (game->viewer.color[i] == 2)
			write(1, YELLOW, 5);
		else if (game->viewer.color[i] == 3)
			write(1, RED, 5);
		else if (game->viewer.color[i] == 4)
			write(1, BLUE, 5);
		ft_printf("%02x ", game->arena[i]);
		write(1, EOC, 4);
	}
	write(1, "\n", 1);
}

/*
** Standard output, prints all the players and the winner.
*/

void		print_result(t_game *game)
{
	int	i;

	ft_putstr("Introducing champions...\n\n");
	i = -1;
	while (++i < game->nb_players)
		ft_printf("Player %d, Name : %s\n-Comment : %s\n-Weight : %d bytes\n\n",
			i + 1, game->player[i].name, game->player[i].comment, \
			game->player[i].prog_len);
	ft_printf("%s a gagne!!\n", game->player[game->last_alive - 1].name);
}
