/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:45:59 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/11 16:23:33 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Initialize the arena and copy champion source code.
*/

static void	init_arena(t_game *game)
{
	int i;
	int index;

	ft_memset(game->arena, 0, MEM_SIZE);
	ft_memset(game->viewer.color, 0, MEM_SIZE);
	ft_memset(game->viewer.cursor, 0, MEM_SIZE);
	ft_memset(game->viewer.bold, 0, MEM_SIZE);
	i = -1;
	while (++i < game->nb_players)
	{
		index = i * MEM_SIZE / game->nb_players;
		game->viewer.cursor[index] = i + 6;
		ft_memset(game->viewer.color + index, i + 1, game->player[i].prog_len);
		ft_memcpy(game->arena + index, game->player[i].prog, \
				CHAMP_MAX_SIZE);
	}
}

/*
** Create the first proc of each players.
*/

static char	create_proc(t_game *game)
{
	t_proc	*new;
	int		i;
	int		j;

	i = -1;
	while (++i < game->nb_players && (j = -1))
	{
		if (!(new = (t_proc *)malloc(sizeof(t_proc))))
			return (-1);
		new->next = game->proc;
		game->proc = new;
		new->pc = i * MEM_SIZE / game->nb_players;
		while (++j < REG_NUMBER)
			new->reg[j] = 0;
		new->id = i + 1;
		new->reg[0] = i + 1;
		new->carry = 0;
		new->alive = 1;
		new->cycles_to_wait = 0;
		new->op_code = 0;
		new->jump = 0;
	}
	return (0);
}

/*
** Removes the blanks in the players table.
*/

static void	clear_players_tab(t_game *game)
{
	int i;
	int j;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (!game->player[i].nbr && (j = i + 1))
		{
			while (j < MAX_PLAYERS && !game->player[j].nbr)
				j++;
			game->player[i] = game->player[j];
			game->player[i].nbr = i + 1;
		}
}

/*
** Parse the magic byte and if correct create one player.
*/

char		add_player(t_game *game, unsigned char *file, int nbr, int pl)
{
	if (get_int(file, 0) != COREWAR_EXEC_MAGIC)
		return ((game->error = 6));
	if (game->next_p_num)
	{
		if (game->player[game->next_p_num - 1].nbr)
			game->player[nbr - 1] = game->player[game->next_p_num - 1];
		nbr = game->next_p_num;
		game->next_p_num = 0;
	}
	else if ((nbr = 1))
		while (game->player[nbr - 1].nbr)
			nbr++;
	game->player[nbr - 1].nb_proc = 1;
	game->player[nbr - 1].nbr = nbr;
	if ((game->player[nbr - 1].prog_len = pl) <= 0)
		return ((game->error = 4));
	game->player[nbr - 1].alive = 1;
	ft_memcpy(game->player[nbr - 1].name, file + 4, PROG_NAME_LENGTH);
	ft_memcpy(game->player[nbr - 1].comment, file + PROG_NAME_LENGTH + 12, \
		COMMENT_LENGTH);
	ft_memcpy(game->player[nbr - 1].prog, file + PROG_NAME_LENGTH
		+ COMMENT_LENGTH + 16, CHAMP_MAX_SIZE);
	while (pl <= CHAMP_MAX_SIZE)
		game->player[nbr - 1].prog[pl++] = 0;
	return (0);
}

/*
** Initialize the game data.
*/

char		init_game(t_game *game)
{
	game->proc = NULL;
	game->viewer.button = 0;
	game->viewer.sleep = 100000;
	clear_players_tab(game);
	init_arena(game);
	set_op_tab(game);
	get_functions(game);
	if (create_proc(game))
		return ((game->error = 5));
	game->last_alive = game->nb_players;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->nb_check = 0;
	game->cycle = 0;
	game->tot_cycle = 0;
	game->nb_lives = 0;
	game->running = 1;
	return (0);
}
